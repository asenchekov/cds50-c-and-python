# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

### longest word in the English language.

## According to its man page, what does `getrusage` do?

### returns resource usage measures.

## Per that same man page, how many members are in a variable of type `struct rusage`?

### 16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

### I thik it's because they are pointers.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

### The for loop starts by reading character from the file stream and checking if it is 'EOF'.
### Then if statement lets through only alpabetical characters or appostrophies.
### Append character to word.
### If statement Ignores alphabetical strings too long to be words.
### An else if statement checks if word has numerical characters.
### Then an else if statement checks if we have found whole word. Puts a termination sign at the end of the word and calls spellchecking function. Prints the misspelled word.


## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

### I think if we would have used the whole word at a time is that we dont know how long is the word that we are reading.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

### Because these values must not be changed by these functions;
