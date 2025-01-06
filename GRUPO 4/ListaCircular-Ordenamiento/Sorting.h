#ifndef SORTING_H
#define SORTING_H

#include <bits/stdc++.h>
#include "Autor.h"
#include "Libro.h"

class Sorting {
public:
    static void sortBackup(const std::string &inputFile, const std::string &outputFile, const std::string &section, const std::string &field);

private:
    static bool compareAuthors(const std::vector<std::string> &a, const std::vector<std::string> &b, const std::string &field);
    static bool compareBooks(const std::vector<std::string> &a, const std::vector<std::string> &b, const std::string &field);
    static std::vector<std::string> splitLines(std::istream &input, const std::string &terminator);
    static void writeLines(std::ostream &output, const std::vector<std::string> &lines);
};

void Sorting::sortBackup(const std::string &inputFilee, const std::string &outputFile, const std::string &section, const std::string &field) {
    std::string inputFile = "Backup/" + inputFilee;
    std::ifstream in(inputFile);
    std::ofstream out(outputFile);
    if (!in.is_open()) {
        std::cerr << "Error: Unable to open input file: " << inputFile << std::endl;
        return;
    }
    if (!out.is_open()) {
        std::cerr << "Error: Unable to open output file: " << outputFile << std::endl;
        return;
    }

    std::string line;
    std::vector<std::string> authors, books;
    bool inAuthors = false, inBooks = false;

    // Parse the input file
    while (std::getline(in, line)) {
        if (line == "Autores:") {
            inAuthors = true;
            inBooks = false;
            continue;
        }
        if (line == "Libros:") {
            inBooks = true;
            inAuthors = false;
            continue;
        }

        if (inAuthors) {
            authors.push_back(line);
        } else if (inBooks) {
            books.push_back(line);
        }
    }

    // Debugging: Check parsed data
    std::cout << "Parsed Authors: " << authors.size() << " lines" << std::endl;
    std::cout << "Parsed Books: " << books.size() << " lines" << std::endl;

    // Sort Authors
    if (section == "Autores" && !authors.empty()) {
        std::vector<std::vector<std::string>> authorRecords;
        for (size_t i = 0; i < authors.size(); i += 5) {
            if (i + 4 < authors.size()) { // Ensure complete record
                authorRecords.push_back({authors[i], authors[i + 1], authors[i + 2], authors[i + 3], authors[i + 4]});
            }
        }
        std::sort(authorRecords.begin(), authorRecords.end(), 
                  [field](const auto &a, const auto &b) { return compareAuthors(a, b, field); });
        authors.clear();
        for (const auto &record : authorRecords) {
            for (const auto &value : record) authors.push_back(value);
        }
    }

    // Sort Books
    if (section == "Libros" && !books.empty()) {
        std::vector<std::vector<std::string>> bookRecords;
        for (size_t i = 0; i < books.size(); i += 8) {
            if (i + 7 < books.size()) { // Ensure complete record
                bookRecords.push_back({books[i], books[i + 1], books[i + 2], books[i + 3],
                                       books[i + 4], books[i + 5], books[i + 6], books[i + 7]});
            }
        }
        std::sort(bookRecords.begin(), bookRecords.end(), 
                  [field](const auto &a, const auto &b) { return compareBooks(a, b, field); });
        books.clear();
        for (const auto &record : bookRecords) {
            for (const auto &value : record) books.push_back(value);
        }
    }

    // Debugging: Check sorted data
    std::cout << "Sorted Authors: " << authors.size() << " lines" << std::endl;
    std::cout << "Sorted Books: " << books.size() << " lines" << std::endl;

    in.close();

    // Write sorted data
    out << "Autores:\n";
    for (const auto &line : authors) out << line << "\n";
    out << "Libros:\n";
    for (const auto &line : books) out << line << "\n";

    out.close();
}

bool Sorting::compareAuthors(const std::vector<std::string> &a, const std::vector<std::string> &b, const std::string &field) {
    static std::unordered_map<std::string, int> indices = {{"Cedula", 0}, {"Nombre", 1}, {"Apellido", 2}, {"Nacionalidad", 3}, {"FechaNacimiento", 4}};
    return a[indices[field]] < b[indices[field]];
}

bool Sorting::compareBooks(const std::vector<std::string> &a, const std::vector<std::string> &b, const std::string &field) {
    static std::unordered_map<std::string, int> indices = {
        {"Id", 0}, {"Nombre", 1}, {"CedulaAutor", 2}, {"Editorial", 3},
        {"Genero", 4}, {"Serie", 5}, {"Rating", 6}, {"FechaPublicacion", 7}
    };
    return a[indices[field]] < b[indices[field]];
}

#endif // SORTING_H
