# OOP-Based Hospital Management System

## Overview

The OOP-Based Hospital Management System is a project designed to manage hospital operations effectively using Object-Oriented Programming (OOP) principles. It includes functionalities for handling patient and doctor data, managing appointments, and more.

## Features

- **Encapsulation**: Protects the internal state of objects by exposing only necessary operations.
- **Inheritance**: Allows the creation of specialized classes (Doctor, Patient) from a base class (Person).
- **Polymorphism**: Enables calling of derived class methods through base class pointers.
- **Abstraction**: Simplifies complex hospital operations by providing a clear interface.

## Project Structure
```bash

OOP-Hospital-Management
├── .vscode # Visual Studio Code configuration files
├── csvFile # Directory for storing CSV data files
├── hospital.cpp # C++ source code
├── hospital.exe # Compiled executable
└── class-diagram.drawio # Class diagram for visual representation

```


## Getting Started

### Prerequisites

- A C++ compiler (e.g., g++, clang++)
- Visual Studio Code (optional, for development)

### Installation

1. Clone the repository:
    ```bash
    git clone https://github.com/your-username/OOP-Hospital-Management.git
    ```

2. Navigate to the project directory:
    ```bash
    cd OOP-Hospital-Management
    ```

### Building the Project

To compile the C++ source code, run the following command:

```bash
g++ -o hospital hospital.cpp
```

### Classes and OOP Concepts
## Person Class
The base class for all persons in the system. Contains common attributes and methods such as pid, fName, lName, sex, pAge, mobile, perT, and personType.

## Doctor Class
Inherits from the Person class and adds specific attributes and methods for doctors, such as type and appointmentsBooked.

## Patient Class
Inherits from the Person class and adds specific attributes and methods for patients, such as h, w, hospitalized, and alive.

## Appointment Class
Manages appointments and interacts with both Doctor and Patient classes.
