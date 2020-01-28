import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session, abort
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, total

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd
app.jinja_env.filters["total"] = total

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    rows = db.execute("SELECT * FROM users WHERE id = :userId",
                      userId=session["user_id"])
    shares = db.execute("SELECT * FROM shares WHERE userId = :userId", userId=session["user_id"])
    cash = usd(rows[0]["cash"])
    return render_template("index.html", cash=cash, shares=shares)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Missing symbol", 400)
        if not request.form.get("shares"):
            return apology("Missing shares", 400)
        if not request.form.get("shares").isdigit():
            return apology("Invalid shares", 400)
        symbol = lookup(request.form.get("symbol"))
        if not symbol:
            return apology("Invalid symbol", 400)
        row = db.execute("SELECT * FROM users WHERE id = :user_id",
                         user_id=session["user_id"])
        cost = symbol["price"] * float(request.form.get("shares"))
        db.execute("UPDATE users SET cash= :cash WHERE id= :user_id",
                   cash=row[0]["cash"] - cost, user_id=session["user_id"])
        shares = db.execute("SELECT * FROM shares WHERE userId = :user_id AND stockId LIKE :stock_id",
                            user_id=session["user_id"], stock_id=symbol["symbol"])
        if shares:
            db.execute("UPDATE shares SET shares= :shares WHERE userId= :user_id AND stockId LIKE :stock_id",
                       shares=(shares[0]["shares"] + int(request.form.get("shares"))), user_id=session["user_id"], stock_id=symbol["symbol"])
            db.execute("INSERT INTO history ('userId', 'symbol', 'shares', 'price') VALUES (:userId, :symbol, :shares, :price)",
                       userId=session["user_id"], symbol=symbol["symbol"], shares=request.form.get("shares"), price=symbol["price"])
        else:
            db.execute("INSERT INTO shares ('userId','stockId','name','shares','price') VALUES (:user_id, :stock_id, :name, :shares, :price)",
                       user_id=session["user_id"], stock_id=symbol["symbol"], name=symbol["name"], shares=request.form.get("shares"), price=symbol["price"])
            db.execute("INSERT INTO history ('userId', 'symbol', 'shares', 'price') VALUES (:userId, :symbol, :shares, :price)",
                       userId=session["user_id"], symbol=symbol["symbol"], shares=request.form.get("shares"), price=symbol["price"])
        return redirect("/")
    if request.method == "GET":
        return render_template("buy.html")


@app.route("/check", methods=["GET"])
def check():
    username = request.args.get("username")
    """Return true if username available, else false, in JSON format"""
    if not username:
        return jsonify(False), 200
    rows = db.execute("SELECT * FROM users WHERE username = :username",
                      username=username)
    if rows:
        return jsonify(False), 200
    else:
        return jsonify(True), 200


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT * FROM history WHERE userId = :userId", userId=session["user_id"])
    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("symbol") and not request.form.get("ajax_symbol"):
            return apology("Missing symbol", 400)
        # print(request.form.get("symbol"))
        if request.form.get("symbol") and not request.form.get("ajax_symbol"):
            quote = lookup(request.form.get("symbol"))
            if not quote:
                return apology("Invalid symbol", 400)
            quote["price"] = usd(quote["price"])
            return render_template("quote.html", quote=quote)
        quote = lookup(request.form.get("ajax_symbol"))
        if not quote:
            return abort(400)
        quote["price"] = usd(quote["price"])
        return jsonify(quote)
    if request.method == "GET":
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("Username taken", 400)
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))
        if rows:
            return apology("Username taken", 400)
        if not request.form.get("password") and not request.form.get("confirmation"):
            return apology("Please provide password", 400)
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("Paswords don't match", 400)
        password = generate_password_hash(request.form.get("password"))
        username = request.form.get("username")
        db.execute("INSERT INTO users ('id','username','hash') VALUES (NULL, :username, :password)",
                   username=username, password=password)
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=username)
        session["user_id"] = rows[0]["id"]
        return redirect("/")
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = None
        shares = None
        if request.form.get("symbol"):
            symbol = request.form.get("symbol")
        if request.form.get("shares"):
            shares = request.form.get("shares")
        if not symbol:
            return apology("Missing symbol", 400)
        if symbol and not shares:
            return apology("Missing shares", 400)
        row = db.execute("SELECT * FROM shares WHERE userId= :userId AND stockId= :stockId",
                         userId=session["user_id"], stockId=symbol)
        if row[0]['shares'] < int(shares):
            return apology("Not enough shares", 400)
        else:
            price = lookup(symbol)
            db.execute("UPDATE shares SET shares= :shares WHERE userId= :userId AND stockId= :stockId",
                       shares=row[0]["shares"] - int(shares), userId=session["user_id"], stockId=symbol)
            db.execute("INSERT INTO history ('userId', 'symbol', 'shares', 'price') VALUES (:userId, :symbol, :shares, :price)",
                       userId=session["user_id"], symbol=symbol, shares=int(shares) * -1, price=price["price"])
            row = db.execute("SELECT * FROM shares WHERE userId= :userId AND stockId= :stockId",
                             userId=session["user_id"], stockId=symbol)
            if row[0]["shares"] == 0:
                db.execute("DELETE FROM shares WHERE userId= :userId AND stockId= :stockId",
                           userId=session["user_id"], stockId=symbol)
            user = db.execute("SELECT * FROM users WHERE id= :userId", userId=session["user_id"])
            profit = int(shares) * price["price"]
            db.execute("UPDATE users SET cash= :cash WHERE id= :user_id",
                       cash=user[0]["cash"] + profit, user_id=session["user_id"])
            return redirect("/")

    if request.method == "GET":
        row = db.execute("SELECT * FROM shares WHERE userId= :userId", userId=session["user_id"])
        # print(row)
        return render_template("sell.html", options=row)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
