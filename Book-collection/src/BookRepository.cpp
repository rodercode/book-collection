#include "../include/BookRepository.h"
#include "../include/Book.h"

BookRepository::BookRepository() {
    // Create a connection
    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "test", "P@ssw0rd!");
    
    // Connect to the MySQL library database
    con->setSchema("librarydb");
}

BookRepository::~BookRepository() {
    // Deallocate memory for res, stmt and con
    delete res;
    delete con;
    delete prep_stmt;
}

// CRUD Operations
void BookRepository::create(Book book) {
    try {
        string queryInsertBook = "INSERT INTO books (title, author, genre_name, user_id) VALUES (?, ?, ?, ?)";
        prep_stmt = con->prepareStatement(queryInsertBook);

        prep_stmt->setString(1, book.getTitle());
        prep_stmt->setString(2, book.getAuthor());
        prep_stmt->setString(3, book.getGenreName());
        prep_stmt->setInt(4, book.getUserId());

        prep_stmt->execute();
    }
    catch (sql::SQLException& e) {
        std::cout << "Error: " << e.what();
        return;
    }

    cout << "Book with name: " << book.getTitle() << " was successfully created" << endl;
}

Book BookRepository::getById(int id) {
    try {
        string query = "SELECT * FROM books WHERE book_id = ?";
        prep_stmt = con->prepareStatement(query);
        prep_stmt->setInt(1, id);
        res = prep_stmt->executeQuery();

        if (res->next()) {
            return Book(
                res->getInt("book_id"),
                res->getString("title"),
                res->getString("author"),
                res->getString("genre_name"),
                res->getInt("user_id")
            );
        }
        else {
            cout << "No book found with ID: " << id << endl;
        }
    }
    catch (sql::SQLException& e) {
		std::cout << "Error: " << e.what();
    }
}

vector<Book> BookRepository::getAll(int userId){
    vector<Book> books;
    
    try {
        string querySelectBooks = "SELECT * FROM books WHERE user_id = ?";
        prep_stmt = con->prepareStatement(querySelectBooks);
        prep_stmt->setInt(1, userId);
        res = prep_stmt->executeQuery();    
        
        while (res->next()) {
            books.emplace_back(
                res->getInt("book_id"),
                res->getString("title"),
                res->getString("author"),
                res->getString("genre_name"),
                res->getInt("user_id")
            );
        }
    }
    catch (sql::SQLException& e) {
        cout << "Error: " << e.what();
    }
    
    return books;
}

void BookRepository::updateById(Book& book) {
    
    try {
        string getBookQuery = "SELECT * FROM books WHERE book_id = ?";
        prep_stmt = con->prepareStatement(getBookQuery);
        prep_stmt->setInt(1, book.getBookId());
        res = prep_stmt->executeQuery();

        if (!res->next()) {
            cout << "No book found with ID: " << book.getBookId() << endl;
            return;
        }

        string updateBookQuery = 
            "UPDATE books SET title = ?, author = ?, genre_name = ? WHERE book_id = ?";
        
        prep_stmt = con->prepareStatement(updateBookQuery);

        prep_stmt->setString(1, book.getTitle());
        prep_stmt->setString(2, book.getAuthor());
        prep_stmt->setString(3, book.getGenreName());
        prep_stmt->setInt(4, book.getBookId()); 
        
        prep_stmt->execute();

        cout << "Book with id: " << book.getBookId() << " was successfully updated" << endl;
    }
    catch (sql::SQLException& e) {
        cout << "Error: " << e.what();
    }
}

void BookRepository::deleteById(int bookId, int userId) {
    
    try {
        string getBookQuery = "SELECT * FROM books WHERE book_id = ?";
        prep_stmt = con->prepareStatement(getBookQuery);
        prep_stmt->setInt(1, bookId);
        res = prep_stmt->executeQuery();

        if (!res->next()) {
            cout << "No book found with ID: " << bookId << endl;
            return;
        }

        if (res->getInt("user_id") != userId) {
			cout << "You can only delete books that you have created" << endl;
			return;
		}
        
        string deleteQuery = "DELETE FROM books WHERE book_id = ?";
        prep_stmt = con->prepareStatement(deleteQuery);
        prep_stmt->setInt(1, bookId);
        prep_stmt->execute();
    }
    catch (sql::SQLException& e) {
        cout << "Error: " << e.what();
        return;
    }

    cout << "Book with id: " << bookId << " was successfully deleted" << endl;
}