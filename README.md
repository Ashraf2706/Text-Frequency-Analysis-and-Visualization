
# Text Frequency Analysis and Visualization

## Overview
This project analyzes text data to identify word frequencies and visualizes the results as bar charts. It utilizes linked lists for managing word data, and various preprocessing techniques to clean and structure the text data for analysis.

## Features

### Text Analysis
- **Load File**: Read input text files and preprocess the content by removing punctuation and converting all text to lowercase.
- **Remove Common Words**: Optionally filter out commonly used words (e.g., "and", "the") from the analysis.
- **Remove Low Frequency Words**: Optionally remove words that occur only once in the text.
- **Sort Data**: Organize words based on their frequency in descending order.

### Visualization
- **Display Bar Charts**: Generate and display bar charts for word frequencies directly in the console.
- **Export Bar Charts**: Save bar charts to a file in a formatted text output.

### Data Structures
- **Linked List (LL)**: A custom templated linked list class is used for managing word data, supporting operations such as insertion, removal, and traversal.

## Files

### Source Files
1. **`Bar.cpp` & `Bar.h`**:
   - Implements the main analysis and visualization functionalities.
   - Handles file input, preprocessing, filtering, sorting, and exporting.

2. **`LL.cpp`**:
   - Implements the templated linked list class.
   - Provides methods for inserting, finding, and removing nodes, as well as displaying the list.

3. **Input Files**:
   - **`proj5_test1.txt`**: Contains text about sports and their cultural significance.
   - **`proj5_test2.txt`**: Discusses sunscreen and its effectiveness.

### Key Classes

#### `Bar` Class
- **Attributes**:
  - `string m_fileName`: The name of the input file.
  - `LL<string>* m_data`: A linked list to store word data.
  - `multimap<int, string> m_dataSorted`: A multimap to sort data based on frequency.
- **Core Methods**:
  - `Start`: Initiates the analysis and visualization process.
  - `LoadFile`: Reads and preprocesses text from the input file.
  - `RemoveCommon`: Filters out common words.
  - `RemoveSingles`: Removes words with a frequency of 1.
  - `SortData`: Sorts words based on frequency.
  - `DisplayBars`: Displays bar charts in the console.
  - `Export`: Saves bar charts to a file.

#### `LL` Class
- **Attributes**:
  - `Node<T>* m_head`: Pointer to the head of the linked list.
  - `int m_size`: Number of nodes in the list.
- **Core Methods**:
  - `Insert`: Inserts a word or increments its frequency if it already exists.
  - `RemoveAt`: Removes a node with a specific value.
  - `Display`: Displays the content of the list.
  - `GetSize`: Returns the number of nodes in the list.

## Installation and Execution

1. Compile the program:
   ```bash
   g++ -o text_analysis Bar.cpp LL.cpp
   ```
2. Run the program:
   ```bash
   ./text_analysis
   ```

### Usage Instructions
- On running, the program will prompt you to:
  1. Remove common words (yes/no).
  2. Remove words with a frequency of 1 (yes/no).
  3. Display or export the results.

## Example Output

### Bar Chart Display (Console)
```
word1          : *****
word2          : ***
word3          : ****
```

### Exported File
The bar chart is saved in the format:
```
word1          : *****
word2          : ***
word3          : ****
```

## Dependencies
- **Standard C++ Libraries**:
  - `<iostream>`
  - `<fstream>`
  - `<map>`
  - `<string>`
  - `<vector>`
  - `<iomanip>`

## License
This project is for educational purposes and does not include warranties or guarantees.
