[![Quality gate](https://sonarcloud.io/api/project_badges/quality_gate?project=byaketava_LibraryService)](https://sonarcloud.io/summary/new_code?id=byaketava_LibraryService)
# Library service

>This is a simple library project that allows you to manage a collection of books, specifying authors and genres, including adding new books, authors and genres, editing existing ones and deleting outdated entries. 

## Technologies Used
- Java 17
- Spring Boot
- Maven
- PostgreSQL

## Installation
1. Clone the repository
2. Create an application.properties file and add DB parameters:
```properties
spring.datasource.url=jdbc:postgresql://localhost:PORT/YOUR_DB_NAME
spring.datasource.username=YOUR_USERNAME
spring.datasource.password=YOUR_PASSWORD
spring.jpa.hibernate.ddl-auto=update
```
3. Build the project and run the application
The application will start on `http://localhost:8080`

## Interface
Use this adresses to get all books, authors and genres.
```
http://localhost:8080/api/books
http://localhost:8080/api/authors
http://localhost:8080/api/genres
```
Also there are many more endpoints for CRUD operations
