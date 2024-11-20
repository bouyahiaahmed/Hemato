# Hemato-Git Project

## Project Overview
**Hemato-Git** is a desktop application developed in C using Glade 2, designed to manage and facilitate blood donation processes. The application supports multiple user roles, each with specific functionalities, to streamline the management of blood donations, user information, and statistics.

## Features
The project includes comprehensive CRUD operations and statistics for different user roles:
- **Donor**: 
  - Schedule and manage appointments for blood donation.
  - Choose donation locations and times.
- **Admin**:
  - Manage users and establishments with full CRUD functionality.
  - View statistics related to users and establishments.
- **Doctor**:
  - Manage donation files and view donation-related statistics.
- **Nurse**:
  - Manage donor files and access statistics related to donors.
- **Director**:
  - Manage blood requests, including source, blood type, and related details.
  - View statistics, such as the most requested blood types and other relevant data.

## Requirements
- **Programming Language**: C
- **User Interface**: Developed using **Glade 2**
- **Compiler**: GCC (GNU Compiler Collection)

## Installation
1. Clone this repository:
   ```bash
   git clone https://github.com/bouyahiaahmed/Hemato
2. Navigate into the project directory:
   ```bash
   cd hemato
3. Prepares the build configuration files:
   ```bash
   ./autogen.sh
4. Compiles the project and installs the compiled project system-wide (requires administrative privileges)
   ```bash
   make ; sudo make install
5. Run the application :
   ```bash
   hemato
6. Ensure you have Glade 2 installed for UI modifications.
## Usage
- **Run the compiled executable to launch the application.**
- **Follow the prompts or GUI to log in and manage blood donation activities based on your role.**
## Contribution
If you'd like to contribute, please fork the repository and use a feature branch. Pull requests are warmly welcome.
