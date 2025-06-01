FROM maven:3-eclipse-temurin-17-alpine AS build

WORKDIR /app

COPY src/main/resources/checkstyle.xml pom.xml ./
RUN mvn clean verify --fail-never -DskipTests
COPY src ./src
RUN mvn package -DskipTests

FROM eclipse-temurin:17-alpine
WORKDIR /app

COPY --from=build /app/target/Library-0.0.1-SNAPSHOT.jar Library.jar
ENTRYPOINT ["java", "-jar", "Library.jar"]