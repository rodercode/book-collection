## Book Collection Console Application
This console application allows users to manage their book collection. Users can perform various actions such
as adding, reading, updating, and deleting books in their collection. Additionally, new users can register an
account and log in to the system. This README provides instructions on how to set up  and use the application.


## Technologies and Tools
- Visual Studio
- C++
- MySQL

## Getting Started

Follow these steps to set up and run the Application:

1. Clone the Repository
Open your command-line interface and run the following command to clone the Book Collection repository from GitHub:
Clone this repository to your local machine:
   ```bash
   https://github.com/rodercode/book-collection.git

2. Setup MySQL Connector/C++
   - download MySQL connector: https://dev.mysql.com/downloads/connector/cpp/
   - Watch this tutorial how to setup MySQL connector for visual studio
     https://www.youtube.com/watch?v=a_W4zt5sR1M&t=109s
     
3.  Add Existing Files to the Project
    - Open your C++ development environment (e.g., Visual Studio, Code::Blocks).
    - If you see that some files are marked with a red sign (indicating they are missing), follow these steps:
    - Right-click on the solution (or project) in the solution explorer.
    - Select "Add" and then choose "Existing Item..."
    - Navigate to the location of the missing files in the cloned repository and add them to the project.

4. Database Setup:
   Please ensure that your MySQL Server is correctly configured and running. The application expects you to have a functional
   MySQL database in place, which is used for storing user account information and managing your book collection. All the SQL
   queries needed to create the "libraryDB" and populate it with the necessary data can be found in the "SQL" folder for your
   convenience.

6. Run and build the project 
   
