# Cache Memory Simulation

## Project Overview
This project simulates a **cache memory system** with functionalities for handling memory operations like **read (load)** and **write (save)**. The simulation implements cache hit and miss scenarios with policies such as:

### Cache Hit Policies:
1. **Write Through**: Data is written to both the cache and the main memory simultaneously.
2. **Write Back**: Data is written only to the cache, and the dirty bit is set. The main memory is updated only when the data is removed from the cache.

### Cache Miss Policies:
1. **Write Allocate**: On a cache miss, data is loaded into the cache and written to.
2. **Write Around**: On a cache miss, data is written directly to the main memory without caching it.

## Features
- **Linked List Implementation:**
  - The cache is implemented as a singly linked list to store address, data, and a dirty bit.
- **Hexadecimal Addressing:**
  - Addresses and data are handled in both decimal and hexadecimal formats.
- **CSV File Integration:**
  - Reads and writes memory data from a `Memory.csv` file.
- **Dynamic Cache Management:**
  - User-defined cache size.
  - Handles cache capacity and replacement.
- **Interactive Console Menu:**
  - Allows users to choose operations dynamically.

## File Structure
- **`main.cpp`**: Contains the main program logic.
- **`Memory.csv`**: Stores memory addresses and data in CSV format.

## How to Use
1. **Setup Memory File:**
   - Ensure a `Memory.csv` file exists in the project directory with the following format:
     ```csv
     Address,Data
     1A2,FF
     2B3,AA
     ```
2. **Run the Program:**
   - Compile the program using a C++ compiler, e.g.,
     ```bash
     g++ -o CacheSimulator main.cpp
     ./CacheSimulator
     ```
3. **Choose Cache Policies:**
   - Select cache hit and miss policies from the menu.
4. **Perform Operations:**
   - Enter load (read) or save (write) operations.
   - View updated cache and memory states.

## Functionalities
### Cache Operations
1. **Load (Read):**
   - If data exists in the cache (cache hit), it's fetched directly.
   - If data doesn't exist (cache miss), it's fetched from the memory file based on the selected miss policy.

2. **Save (Write):**
   - If data exists in the cache, it's updated based on the selected hit policy.
   - If data doesn't exist, it's handled based on the selected miss policy.

### Cache Display
- Shows the current state of the cache with address, data, and dirty bit.

### Memory Display
- Reads and displays all contents of the `Memory.csv` file.

## Functions and Classes
### Classes
1. **`node`:**
   - Represents a single cache block.
   - Attributes:
     - `adress` (string): Hexadecimal address.
     - `data` (int): Data stored at the address.
     - `dirtybit` (bool): Indicates if data is modified.

2. **`cacheList`:**
   - Represents the cache as a singly linked list.
   - Methods:
     - `search`: Finds a node by address.
     - `write`: Writes data to the cache and/or memory.
     - `writeDatatoFile`: Writes back all modified data to memory.
     - `addNodeAtHead`: Adds a new node at the head of the cache.
     - `display`: Displays the current state of the cache.
     - `displayDataFromFile`: Displays the memory file contents.

### Utility Functions
1. **`intToHex(int num)`:** Converts a decimal integer to a hexadecimal string.
2. **`hexToInt(const string& hexStr)`:** Converts a hexadecimal string to a decimal integer.

## Example Run
```plaintext
Cache hit policy :
1. Write through
2. Write Back
Enter choice: 1
Cache miss policy :
1. Write Allocate
2. Write Around
Enter choice: 1
Enter size of cache: 3

1. Load operation
2. Save operation
Enter choice: 1
Address (Hexadecimal): 1A2
Found (cache hit)!

1. Load operation
2. Save operation
Enter choice: 2
Address (Hexadecimal): 2B3
Enter data (Hexadecimal): BB
Found (cache hit)!
Data written successfully.
```

## Limitations
- The cache does not implement replacement policies like LRU or FIFO when the capacity is exceeded.
- Assumes the `Memory.csv` file exists and is formatted correctly.

## Future Enhancements
- Add support for replacement policies.
- Implement error handling for incorrect inputs or missing files.

## Author
Abdullah

## License
This project is for educational purposes and does not include a formal license.
