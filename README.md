## Usage
```
cudoku <SRC-TYPE> <SRC> [<RENDER>]
  SRC-TYPE:
      -s --string    load sudoku grid from string provided as SRC
      -f --file      load sudoku grid from file provided as SRC
  RENDER:
      -r -i --render-input    render unsolved grid
```

## Data Formatting
An empty space is represented by a zero `0`.<br>
81 numbers are expected, because a sudoku grid is 9x9.<br>
Any non digit characters are ignored.<br>
That means you can make a nice looking grid in a text file using spaces and box making characters, or just paste in a string of 81 digits. Anything will work.<br>
Refrain from using backslashes (`\`) because if one is passed before a digit, it could form an escape character.<br>

## Examples
Solve grid from text file called `somegrid.txt` & render grid before solving:
```
cudoku -f somegrid.txt -r
```
Solve grid from string:
```
cudoku -s 920306000001024600500000001040007000103402706000100080800000002007280900000601037
```
