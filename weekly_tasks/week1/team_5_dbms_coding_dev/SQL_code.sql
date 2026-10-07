DROP DATABASE IF EXISTS LibraryLendingSystem;

CREATE DATABASE LibraryLendingSystem;

USE LibraryLendingSystem;


CREATE TABLE Books (
    book_id INT AUTO_INCREMENT PRIMARY KEY,
    isbn VARCHAR(20) NOT NULL UNIQUE,
    title VARCHAR(200) NOT NULL,
    author VARCHAR(150) NOT NULL,
    publisher VARCHAR(150),
    publication_year YEAR,
    category VARCHAR(100)
);


CREATE TABLE Members (
    member_id INT AUTO_INCREMENT PRIMARY KEY,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    address VARCHAR(200),
    phone VARCHAR(15),
    email VARCHAR(100) NOT NULL UNIQUE,
    membership_date DATE NOT NULL
);


CREATE TABLE Librarians (
    librarian_id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    email VARCHAR(100) NOT NULL UNIQUE,
    hire_date DATE NOT NULL
);


CREATE TABLE Book_Copies (
    copy_id INT AUTO_INCREMENT PRIMARY KEY,
    book_id INT NOT NULL,
    copy_number INT NOT NULL,
    available BOOLEAN DEFAULT TRUE,
    shelf_location VARCHAR(100),

    FOREIGN KEY (book_id)
        REFERENCES Books(book_id),

    UNIQUE (book_id, copy_number)
);


CREATE TABLE Loans (
    loan_id INT AUTO_INCREMENT PRIMARY KEY,
    copy_id INT NOT NULL,
    member_id INT NOT NULL,
    librarian_id INT NOT NULL,
    borrow_date DATE NOT NULL,
    due_date DATE NOT NULL,
    return_date DATE DEFAULT NULL,
    status ENUM('Borrowed', 'Returned', 'Overdue') DEFAULT 'Borrowed',

    FOREIGN KEY (copy_id)
        REFERENCES Book_Copies(copy_id),

    FOREIGN KEY (member_id)
        REFERENCES Members(member_id),

    FOREIGN KEY (librarian_id)
        REFERENCES Librarians(librarian_id),

    CHECK (due_date >= borrow_date),

    CHECK (return_date IS NULL OR return_date >= borrow_date)
);


INSERT INTO Books
(isbn, title, author, publisher, publication_year, category)
VALUES
('9780132350884', 'Clean Code', 'Robert C. Martin', 'Prentice Hall', 2008, 'Programming'),
('9780073523323', 'Database System Concepts', 'Abraham Silberschatz', 'McGraw Hill', 2019, 'Database'),
('9780134685991', 'Effective Java', 'Joshua Bloch', 'Addison Wesley', 2018, 'Programming'),
('9780262033848', 'Introduction to Algorithms', 'Thomas H. Cormen', 'MIT Press', 2009, 'Algorithms');


INSERT INTO Book_Copies
(book_id, copy_number, available, shelf_location)
VALUES
(1, 1, TRUE, 'A-01'),
(1, 2, TRUE, 'A-01'),
(2, 1, TRUE, 'B-05'),
(2, 2, TRUE, 'B-05'),
(2, 3, TRUE, 'B-05'),
(3, 1, TRUE, 'C-10'),
(3, 2, TRUE, 'C-10'),
(4, 1, TRUE, 'D-02');


INSERT INTO Members
(first_name, last_name, address, phone, email, membership_date)
VALUES
('Rohit', 'Chintalapudi', 'Mangalagiri', '9876543210', 'rohit@example.com', '2026-01-10'),
('Rahul', 'Kumar', 'Vijayawada', '9876543211', 'rahul@example.com', '2026-02-15'),
('Anjali', 'Reddy', 'Guntur', '9876543212', 'anjali@example.com', '2026-03-01');


INSERT INTO Librarians
(name, email, hire_date)
VALUES
('Anil Kumar', 'anil@library.com', '2023-01-15'),
('Priya Sharma', 'priya@library.com', '2024-03-10');


DELIMITER //

CREATE PROCEDURE IssueBook(
    IN p_book_id INT,
    IN p_member_id INT,
    IN p_librarian_id INT
)
BEGIN
    DECLARE v_copy_id INT DEFAULT NULL;
    DECLARE v_overdue_count INT DEFAULT 0;

    SELECT COUNT(*)
    INTO v_overdue_count
    FROM Loans
    WHERE member_id = p_member_id
    AND return_date IS NULL
    AND due_date < CURDATE();

    IF v_overdue_count > 0 THEN

        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Member has overdue books and cannot borrow another book';

    ELSE

        SELECT copy_id
        INTO v_copy_id
        FROM Book_Copies
        WHERE book_id = p_book_id
        AND available = TRUE
        LIMIT 1;

        IF v_copy_id IS NULL THEN

            SIGNAL SQLSTATE '45000'
            SET MESSAGE_TEXT = 'No copies of this book are currently available';

        ELSE

            INSERT INTO Loans
            (
                copy_id,
                member_id,
                librarian_id,
                borrow_date,
                due_date,
                status
            )
            VALUES
            (
                v_copy_id,
                p_member_id,
                p_librarian_id,
                CURDATE(),
                DATE_ADD(CURDATE(), INTERVAL 14 DAY),
                'Borrowed'
            );

            UPDATE Book_Copies
            SET available = FALSE
            WHERE copy_id = v_copy_id;

        END IF;

    END IF;

END //

DELIMITER ;


DELIMITER //

CREATE PROCEDURE ReturnBook(
    IN p_loan_id INT
)
BEGIN
    DECLARE v_copy_id INT DEFAULT NULL;

    SELECT copy_id
    INTO v_copy_id
    FROM Loans
    WHERE loan_id = p_loan_id
    AND return_date IS NULL;

    IF v_copy_id IS NULL THEN

        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Invalid loan ID or book already returned';

    ELSE

        UPDATE Loans
        SET
            return_date = CURDATE(),
            status = 'Returned'
        WHERE loan_id = p_loan_id;

        UPDATE Book_Copies
        SET available = TRUE
        WHERE copy_id = v_copy_id;

    END IF;

END //

DELIMITER ;


DELIMITER //

CREATE PROCEDURE UpdateOverdueLoans()
BEGIN

    UPDATE Loans
    SET status = 'Overdue'
    WHERE return_date IS NULL
    AND due_date < CURDATE()
    AND status = 'Borrowed';

END //

DELIMITER ;


CALL IssueBook(1, 1, 1);

CALL IssueBook(2, 2, 1);

CALL IssueBook(3, 3, 2);


SELECT * FROM Books;

SELECT * FROM Book_Copies;

SELECT * FROM Members;

SELECT * FROM Librarians;

SELECT * FROM Loans;


SELECT
    l.loan_id,
    b.title,
    CONCAT(m.first_name, ' ', m.last_name) AS member_name,
    l.borrow_date,
    l.due_date,
    DATEDIFF(CURDATE(), l.due_date) AS overdue_days
FROM Loans l
JOIN Book_Copies bc ON l.copy_id = bc.copy_id
JOIN Books b ON bc.book_id = b.book_id
JOIN Members m ON l.member_id = m.member_id
WHERE l.return_date IS NULL
AND l.due_date < CURDATE();


SELECT
    b.book_id,
    b.title,
    b.author,
    b.isbn,
    COUNT(bc.copy_id) AS available_copies
FROM Books b
JOIN Book_Copies bc ON b.book_id = bc.book_id
WHERE bc.available = TRUE
GROUP BY
    b.book_id,
    b.title,
    b.author,
    b.isbn;


SELECT
    CONCAT(m.first_name, ' ', m.last_name) AS member_name,
    b.title,
    bc.copy_number,
    l.borrow_date,
    l.due_date,
    l.return_date,
    l.status
FROM Loans l
JOIN Members m ON l.member_id = m.member_id
JOIN Book_Copies bc ON l.copy_id = bc.copy_id
JOIN Books b ON bc.book_id = b.book_id
WHERE m.member_id = 1
ORDER BY l.borrow_date DESC;


SELECT
    l.loan_id,
    b.title,
    CONCAT(m.first_name, ' ', m.last_name) AS member_name,
    lib.name AS librarian,
    l.borrow_date,
    l.due_date,
    l.return_date,
    l.status
FROM Loans l
JOIN Book_Copies bc ON l.copy_id = bc.copy_id
JOIN Books b ON bc.book_id = b.book_id
JOIN Members m ON l.member_id = m.member_id
JOIN Librarians lib ON l.librarian_id = lib.librarian_id
ORDER BY l.borrow_date DESC;


SELECT
    b.title,
    COUNT(bc.copy_id) AS total_copies,
    SUM(CASE WHEN bc.available = TRUE THEN 1 ELSE 0 END) AS available_copies,
    SUM(CASE WHEN bc.available = FALSE THEN 1 ELSE 0 END) AS issued_copies
FROM Books b
JOIN Book_Copies bc ON b.book_id = bc.book_id
GROUP BY
    b.book_id,
    b.title;


CALL ReturnBook(1);


SELECT * FROM Loans;


SELECT * FROM Book_Copies;


CALL UpdateOverdueLoans();


SELECT
    l.loan_id,
    b.title,
    CONCAT(m.first_name, ' ', m.last_name) AS member_name,
    l.borrow_date,
    l.due_date,
    l.return_date,
    CASE
        WHEN l.return_date IS NOT NULL THEN 'Returned'
        WHEN l.due_date < CURDATE() THEN 'Overdue'
        ELSE 'Borrowed'
    END AS current_status
FROM Loans l
JOIN Book_Copies bc ON l.copy_id = bc.copy_id
JOIN Books b ON bc.book_id = b.book_id
JOIN Members m ON l.member_id = m.member_id
ORDER BY l.loan_id;


SELECT
    b.title,
    bc.copy_number,
    bc.available,
    bc.shelf_location
FROM Book_Copies bc
JOIN Books b ON bc.book_id = b.book_id
ORDER BY b.title, bc.copy_number;


SELECT
    CONCAT(m.first_name, ' ', m.last_name) AS member_name,
    COUNT(l.loan_id) AS total_books_borrowed
FROM Members m
LEFT JOIN Loans l ON m.member_id = l.member_id
GROUP BY
    m.member_id,
    m.first_name,
    m.last_name;


SELECT
    b.title,
    COUNT(l.loan_id) AS total_times_borrowed
FROM Books b
LEFT JOIN Book_Copies bc ON b.book_id = bc.book_id
LEFT JOIN Loans l ON bc.copy_id = l.copy_id
GROUP BY
    b.book_id,
    b.title
ORDER BY total_times_borrowed DESC;