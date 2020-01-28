import cs50
import csv

from flask import Flask, jsonify, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Reload templates when they are changed
app.config["TEMPLATES_AUTO_RELOAD"] = True


@app.after_request
def after_request(response):
    """Disable caching"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Renders the homepage


@app.route("/", methods=["GET"])
def get_index():
    return redirect("/form")

# renders form on /form


@app.route("/form", methods=["GET"])
def get_form():
    return render_template("form.html")

# proceses the form submition


@app.route("/form", methods=["POST"])
def post_form():
    if not request.form.get("firstName") or not request.form.get("lastName") or not request.form.get("years") or not request.form.get("country") or not request.form.get("gender"):
        return render_template("error.html", message="Sorry, something went wrong.")
    with open("survey.csv", "a") as file:
        writer = csv.DictWriter(file, fieldnames=["firstName", "lastName", "years", "country", "gender"])
        writer.writerow({"firstName": request.form.get("firstName"),
                         "lastName": request.form.get("lastName"), "years": request.form.get("years"), "country": request.form.get("country"), "gender": request.form.get("gender")})
    return redirect("/sheet")

# Shows the survey sheet


@app.route("/sheet", methods=["GET"])
def get_sheet():

    with open("survey.csv", newline='') as file:
        reader = csv.reader(file)
        students = list(reader)
    return render_template("survey.html", students=students)
