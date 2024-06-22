# Banking Management System

## Overview

The Banking Management System is a console-based application implemented in C++ using pure object-oriented programming (OOP) principles. It facilitates user and company account management with various account types and functionalities, storing data using text files.

### Features

- **User Accounts:** Individuals can open accounts categorized into Bronze and Gold types, each with different daily transaction limits.
  - Bronze: Daily limit of 100,000 units.
  - Gold: Daily limit of 500,000 units.
- **Company Accounts:** Businesses can open shared accounts with a higher daily limit.
  - Business: Daily limit of 2,000,000 units.
- **Account Approval:** Opening a user account requires approval from designated employees. They can accept or reject account requests.
- **Card Assignment:** Upon approval, users receive a 16-digit card number and are prompted to set a PIN for their card.
- **CEO Login:** The CEO has a hidden login option accessible by entering a specific code (34592). Only the CEO can open company accounts.

### Instructions

- Follow the prompts to navigate through the menu options.
- Users can apply for accounts, check balances, make transactions, send money to other account, check their transaction history.
- The owner of companyclient account can grant access to the account to any user account of bank(granting access to its employees).
- CEO login is available by entering the access code (34592) to manage company accounts.
- Employees handle account approval requests, check anyone's transaction history and accept or rejct loan requests from companies accounts.
- Daily limits are automatically resetted according to the time of local machine.

## Implementation Details

This project is implemented using pure object-oriented programming (OOP) principles in C++. It utilizes classes, inheritance, and aggregation for managing user and company accounts. Data storage is handled using text files for persistence and retrieval.

### Dependencies

- The project uses standard C++ libraries. Ensure a compatible compiler environment for compilation and execution.

## Contributors

- **Muhammad Ali**: [GitHub Profile](https://github.com/MuhammadAli990)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
