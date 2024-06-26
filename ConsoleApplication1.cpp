#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

struct Song {
    string title;
    string author;
    int year;
    string lyrics;
};

vector<Song> songCatalog;

void addSong() {
    Song newSong;
    cout << "Enter song title: ";
    getline(cin, newSong.title);
    cout << "Enter author: ";
    getline(cin, newSong.author);
    cout << "Enter year of creation (0 if unknown): ";
    cin >> newSong.year;
    cin.ignore();
    cout << "Enter lyrics (end with an empty line):\n";
    string line, lyrics;
    while (getline(cin, line) && !line.empty()) {
        lyrics += line + "\n";
    }
    newSong.lyrics = lyrics;
    songCatalog.push_back(newSong);
    cout << "Song added successfully!\n";
}

void addSongFromFile() {
    Song newSong;
    string filename;
    cout << "Enter the filename: ";
    cin >> filename;
    ifstream file(filename);
    if (file.is_open()) {
        getline(file, newSong.title);
        getline(file, newSong.author);
        file >> newSong.year;
        file.ignore();
        string line, lyrics;
        while (getline(file, line)) {
            lyrics += line + "\n";
        }
        newSong.lyrics = lyrics;
        songCatalog.push_back(newSong);
        cout << "Song added from file successfully!\n";
    }
    else {
        cout << "Error opening file.\n";
    }
}

void deleteSong() {
    string title;
    cout << "Enter the title of the song to delete: ";
    getline(cin, title);
    auto it = find_if(songCatalog.begin(), songCatalog.end(), [&](const Song& song) {
        return song.title == title;
        });
    if (it != songCatalog.end()) {
        songCatalog.erase(it);
        cout << "Song deleted successfully!\n";
    }
    else {
        cout << "Song not found.\n";
    }
}

void editSong() {
    string title;
    cout << "Enter the title of the song to edit: ";
    getline(cin, title);
    auto it = find_if(songCatalog.begin(), songCatalog.end(), [&](const Song& song) {
        return song.title == title;
        });
    if (it != songCatalog.end()) {
        Song& song = *it;
        cout << "Editing song: " << song.title << "\n";
        cout << "Enter new title (or press enter to keep the current): ";
        string newTitle;
        getline(cin, newTitle);
        if (!newTitle.empty()) {
            song.title = newTitle;
        }
        cout << "Enter new author (or press enter to keep the current): ";
        string newAuthor;
        getline(cin, newAuthor);
        if (!newAuthor.empty()) {
            song.author = newAuthor;
        }
        cout << "Enter new year (or 0 to keep the current): ";
        int newYear;
        cin >> newYear;
        cin.ignore();
        if (newYear != 0) {
            song.year = newYear;
        }
        cout << "Enter new lyrics (end with an empty line):\n";
        string line, newLyrics;
        while (getline(cin, line) && !line.empty()) {
            newLyrics += line + "\n";
        }
        if (!newLyrics.empty()) {
            song.lyrics = newLyrics;
        }
        cout << "Song edited successfully!\n";
    }
    else {
        cout << "Song not found.\n";
    }
}

void displaySong() {
    string title;
    cout << "Enter the title of the song to display: ";
    getline(cin, title);
    auto it = find_if(songCatalog.begin(), songCatalog.end(), [&](const Song& song) {
        return song.title == title;
        });
    if (it != songCatalog.end()) {
        const Song& song = *it;
        cout << "Title: " << song.title << "\n";
        cout << "Author: " << song.author << "\n";
        cout << "Year: " << song.year << "\n";
        cout << "Lyrics:\n" << song.lyrics << "\n";
    }
    else {
        cout << "Song not found.\n";
    }
}

void saveSongToFile() {
    string title, filename;
    cout << "Enter the title of the song to save: ";
    getline(cin, title);
    cout << "Enter the filename to save the song: ";
    getline(cin, filename);
    auto it = find_if(songCatalog.begin(), songCatalog.end(), [&](const Song& song) {
        return song.title == title;
        });
    if (it != songCatalog.end()) {
        const Song& song = *it;
        ofstream file(filename);
        if (file.is_open()) {
            file << song.title << "\n";
            file << song.author << "\n";
            file << song.year << "\n";
            file << song.lyrics;
            file.close();
            cout << "Song saved to file successfully!\n";
        }
        else {
            cout << "Error opening file.\n";
        }
    }
    else {
        cout << "Song not found.\n";
    }
}

void searchByAuthor() {
    string author;
    cout << "Enter the author to search for: ";
    getline(cin, author);
    cout << "Songs by " << author << ":\n";
    for (const auto& song : songCatalog) {
        if (song.author == author) {
            cout << "- " << song.title << " (" << song.year << ")\n";
        }
    }
}

void searchByKeyword() {
    string keyword;
    cout << "Enter the keyword for search: ";
    getline(cin, keyword);
    cout << "Songs containing \"" << keyword << "\":\n";
    for (const auto& song : songCatalog) {
        if (song.lyrics.find(keyword) != string::npos) {
            cout << "- " << song.title << " by " << song.author << " (" << song.year << ")\n";
        }
    }
}

int main() {
    while (true) {
        cout << "1. Add song\n";
        cout << "2. Add song from file\n";
        cout << "3. Delete song\n";
        cout << "4. Edit song\n";
        cout << "5. Display song\n";
        cout << "6. Save song as a file\n";
        cout << "7. Search by author\n";
        cout << "8. Search by keyword\n";
        cout << "9. Exit\n";
        cout << "Shose option: ";
        int choice;
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1: addSong(); break;
        case 2: addSongFromFile(); break;
        case 3: deleteSong(); break;
        case 4: editSong(); break;
        case 5: displaySong(); break;
        case 6: saveSongToFile(); break;
        case 7: searchByAuthor(); break;
        case 8: searchByKeyword(); break;
        case 9: return 0;
        default: cout << "Invalid option, try again.\n";
        }
    }
    return 0;
}
    