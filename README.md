# Simple Bank Management System (C++)

A professional command-line banking application developed in C++ showcasing robust software engineering principles.

## 🚀 Key Features
- **Client Management:** Full CRUD operations (Create, Read, Update, Delete).
- **Transaction System:** Secure Deposit, Withdrawal, and Total Balances calculation.
- **Data Persistence:** Automatic data saving and loading using text files.
- **Robust Validation:** Advanced input validation to prevent program crashes.

## 🛠️ Technical Skills Demonstrated
- **Modular Programming:** Separation of logic into multiple files and functions.
- **File Handling:** Managing data storage using `fstream`[cite: 1, 15, 26, 52].
- **Data Structures:** Efficient use of `std::vector` and `structs` for data management[cite: 2, 3, 26].
- **String Manipulation:** Custom string splitting and processing algorithms[cite: 3, 9].

## 💻 Screenshots

1. Main Menu List:
![alt text](<Screenshot 2026-01-31 011903.png>)
The central hub of the application. It employs a Modular Switch-Case architecture and a do-while loop to manage the program's lifecycle. Every input is validated via a custom ReadInt function to ensure system stability and prevent crashes.

2. Show Client List:
![alt text](<Screenshot 2026-01-31 011939.png>)
Displays a comprehensive and formatted table of all registered clients. It uses std::left and setw for precise alignment, providing a clean data overview.

3. Add New Client:
![alt text](<Screenshot 2026-01-31 012118.png>)
Allows the creation of new client records. The system includes a validation check to ensure that account numbers are unique and do not already exist in the database.

4. Delete Client:
![alt text](<Screenshot 2026-01-31 012224.png>)
Performs a secure deletion of client records. It uses a 'Mark for Delete' logic to ensure data is handled safely before being permanently removed from the file.

5. Update Client Info:
![alt text](<Screenshot 2026-01-31 013801.png>)
Provides the ability to modify existing client details (PIN, Name, Phone, Balance). Changes are reflected in the vector and then synced with the text database.

6. Find Client:
![alt text](<Screenshot 2026-01-31 014053.png>)
A quick search feature that retrieves a specific client's details by their unique account number and displays them in an organized 'Client Card'.

7. Transactions:
![alt text](<Screenshot 2026-01-31 012005.png>)
A dedicated sub-menu for financial operations including Deposits, Withdrawals with balance checks, and Total Balance reports.

7. Exit:
![alt text](<Screenshot 2026-01-31 014432.png>)
Ensures a clean termination of the program, providing a final status message to the user.