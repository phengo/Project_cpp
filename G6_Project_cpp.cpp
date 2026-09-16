#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <limits>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Song {
    int id;
    string title;
    string artist;
    string album;
    string url;
};

struct StackNode {
    Song song;
    StackNode *next;
};

class RecentlyPlayed{
    private:
        StackNode* top;
    public:
        RecentlyPlayed() : top(nullptr) {}
        void push(Song song) {
            StackNode *newNode = new StackNode;
            newNode->song = song;
            newNode->next = top;
            top = newNode;
        }
        Song pop() {
            if (top == nullptr) {
                cout << "Recently played list is empty!\n";
                return Song();
            }
            StackNode *temp = top;
            Song song = temp->song;
            top = top->next;
            delete temp;
            return song;
        }
        void viewRecentlyPlayed(){
            if (top == nullptr) {
                cout << "\n===== RECENTLY PLAYED =====\n";
                cout << "Recently played list is empty!\n";
                return;
            }
            cout << "\n===== RECENTLY PLAYED =====\n";
            StackNode *current = top;
            while (current != nullptr) {
                cout << "ID: " << current->song.id << endl;
                cout << "Title: " << current->song.title << endl;
                cout << "Artist: " << current->song.artist << endl;
                cout << "Album: " << current->song.album << endl;
                cout << "------------------------\n";
                current = current->next;
            }
        }
};

struct QueueNode {
    Song song;
    QueueNode *next;
};

class PlayQueue {
private:
    QueueNode* front;
    QueueNode* rear;
public:
    PlayQueue() : front(nullptr), rear(nullptr) {}
    void enqueue(Song song) {
        QueueNode *newNode = new QueueNode;
        newNode->song = song;
        newNode->next = nullptr;
        if(front == nullptr) {
            front = newNode;
            rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        cout << "Song added to the play queue successfully!\n";
    }
    Song dequeue() {
        if (front == nullptr) {
            cout << "Play queue is empty!\n";
            return Song();
        }
        QueueNode *temp = front;
        Song song = temp->song;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        return song;
    }
    void ViewQueue() {
        if (front == nullptr) {
            cout << "Play queue is empty!\n";
            return;
        }
        QueueNode *current = front;
        cout << "\n===== PLAY QUEUE =====\n";
        while (current != nullptr) {
            cout << "ID: " << current->song.id << endl;
            cout << "Title: " << current->song.title << endl;
            cout << "Artist: " << current->song.artist << endl;
            cout << "Album: " << current->song.album << endl;
            cout << "URL: " << current->song.url << endl;
            cout << "------------------------\n";
            current = current->next;
        }
    }
    bool empty() {
        return front == nullptr;
    }
};

struct Node {
    Song song;
    Node *next;
    Node *prev;
};

class Playlist {
    private:
    Node *head;
    Node *tail;
    Node *current;
    public:
    Playlist(){
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }
    void addSong(){
        Song song;
        cout << "\n===== ADD SONG =====\n";
        cout << "Enter ID: ";
        cin >> song.id;
        cout << "Enter Title: ";
        cin.ignore();
        getline(cin, song.title);
        cout << "Enter Artist: ";
        getline(cin, song.artist);
        cout << "Enter Album: ";
        getline(cin, song.album);
        cout << "Enter URL: ";
        getline(cin, song.url);

        Node *newNode = new Node();
        newNode->song = song;
        newNode->next = nullptr;
        newNode->prev = nullptr;

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            current = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        cout << "Song added successfully!\n";
    };
    void viewPlaylist(){
        cout << "\n========================= PLAYLIST =========================\n";
        cout << left
            << setw(5)  << "ID"
            << setw(20) << "TITLE"
            << setw(20) << "ARTIST"
            << setw(20) << "ALBUM"
            << setw(30) << "URL"
            << endl;
        cout << "------------------------------------------------------------\n";
        Node *current = head;
        while (current != nullptr) {
            cout << left
                << setw(5)  << current->song.id
                << setw(20) << current->song.title
                << setw(20) << current->song.artist
                << setw(20) << current->song.album
                << setw(30) << current->song.url
                << endl;
            current = current->next;
        }
    };
    void selectSong() {
        int id;
        cout << "\nEnter Song ID: ";
        cin >> id;
        Node *current = head;
        while (current != nullptr) {
            if (current->song.id == id) {
                cout << "\n===== SONG FOUND =====\n";
                cout << "ID: " << current->song.id << endl;
                cout << "Title: " << current->song.title << endl;
                cout << "Artist: " << current->song.artist << endl;
                cout << "Album: " << current->song.album << endl;
                cout << "URL: " << current->song.url << endl;
                return;
            }
            current = current->next;
        }
        cout << "Song not found!\n";
    }
    void updateSong(){
        cout << "\n===== UPDATE SONG =====\n";
        cout << "Enter Song ID: ";
        int id;
        cin >> id;
        Node *current = head;
        while (current != nullptr) {
            if (current->song.id == id) {
                cout << "Enter new Title: ";
                cin.ignore();
                getline(cin, current->song.title);
                cout << "Enter new Artist: ";
                getline(cin, current->song.artist);
                cout << "Enter new Album: ";
                getline(cin, current->song.album);
                cout << "Enter new URL: ";
                getline(cin, current->song.url);
                cout << "Song updated successfully!\n";
                return;
            }
            current = current->next;
        }
        cout << "Song not found!\n";
    };
    void deleteSong(){
        cout << "\n===== DELETE SONG =====\n";
        cout << "Enter Song ID: ";
        int id;
        cin >> id;
        Node *current = head;
        while (current != nullptr) {
            if (current->song.id == id) {
                if (current->prev != nullptr) {
                    current->prev->next = current->next;
                } else {
                    head = current->next;
                }
                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                } else {
                    tail = current->prev;
                }
                if (current == this->current) {
                    if (current->next != nullptr)
                        this->current = current->next;
                    else
                        this->current = current->prev;
                }
                delete current;
                if (head == nullptr) {
                    this->current = nullptr;
                }
                cout << "Song deleted successfully!\n";
                return;
            }
            current = current->next;
        }
        cout << "Song not found!\n";
    };
    void searchSong() {
        cout << "\n===== SEARCH SONG =====\n";
        cout << "Enter Song Title: ";
        string title;
        cin.ignore();
        getline(cin, title);
        Node *current = head;
        bool found = false;
        while (current != nullptr) {
            if (current->song.title == title) {
                cout << "\n===== SONG FOUND =====\n";
                cout << "ID: " << current->song.id << endl;
                cout << "Title: " << current->song.title << endl;
                cout << "Artist: " << current->song.artist << endl;
                cout << "Album: " << current->song.album << endl;
                cout << "URL: " << current->song.url << endl;
                found = true;
                cout << "Do you want to listen to this song? (y/n): ";
                char choice;
                cin >> choice;
                if (choice == 'y' || choice == 'Y') {
                    cout << "Title: " << current->song.title << endl;
                    cout << "URL: " << current->song.url << endl;
                }else {
                    cout << "Returning to main menu.\n";
                }
                break;
            }
            current = current->next;
        }
        if (!found) {
            cout << "Song not found!\n";
        }
    };
    void sortPlaylist() {
        if (head == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }
        for (Node *i = head; i != nullptr; i = i->next) {
            for (Node *j = i->next; j != nullptr; j = j->next) {
                if (i->song.title > j->song.title) {
                    swap(i->song, j->song);
                }
            }
        }
        cout << "Playlist sorted by title successfully!\n";
    };
    Song* findSong(int id) {
        Node *current = head;
        while (current != nullptr) {
            if (current->song.id == id) {
                return &(current->song);
            }
            current = current->next;
        }
        return nullptr;
    }
    void playSong(RecentlyPlayed &recent) {
        int id;
        cout << "\n===== PLAY SONG =====\n";
        cout << "Enter Song ID: ";
        cin >> id;
        Node *temp = head;
        while (temp != nullptr) {
            if (temp->song.id == id) {
                current = temp;
                recent.push(temp->song);
                cout << "Now playing: " << temp->song.title << " by " << temp->song.artist << endl;
                cout << "URL: " << temp->song.url << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Song not found!\n";
    }
    void playNextsong(RecentlyPlayed &recent) {
        if (current == nullptr) {
            cout << "No song is currently playing!\n";
            return;
        }
        if (current->next == nullptr) {
            cout << "This is the last song in the playlist!\n";
            return;
        }
        current = current->next;
        recent.push(current->song);
        cout << "Now playing: " << current->song.title << " by " << current->song.artist << endl;
        cout << "URL: " << current->song.url << endl;
    }
    void playPreviousSong(RecentlyPlayed &recent) {
        if (current == nullptr) {
            cout << "No song is currently playing!\n";
            return;
        }
        if (current->prev == nullptr) {
            cout << "This is the first song in the playlist!\n";
            return;
        }
        current = current->prev;
        recent.push(current->song);
        cout << "Now playing: " << current->song.title << " by " << current->song.artist << endl;
        cout << "URL: " << current->song.url << endl;
    }
    void showAlbums() {
        if (head == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }
        cout << "\n===== ALBUM =====\n";
        Node *current = head;
        vector<string> albums;
        while (current != nullptr) {
            bool found = false;
            for (string &album : albums) {
                if (album == current->song.album) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                albums.push_back(current->song.album);
            }
            current = current->next;
        }
        for (int i = 0; i < albums.size(); i++) {
            cout << i + 1 << ". " << albums[i] << endl;
        }
        cout << "Enter Album Number: ";
        int choice;
        cin >> choice;
        if (choice < 1 || choice > albums.size()) {
            cout << "Invalid album!\n";
            return;
        }
        cout << "\n===== " << albums[choice - 1] << " =====\n";
        current = head;
        while (current != nullptr) {
            if (current->song.album == albums[choice - 1]) {
                cout << "ID: " << current->song.id << endl;
                cout << "Title: " << current->song.title << endl;
                cout << "Artist: " << current->song.artist << endl;
                cout << "URL: " << current->song.url << endl;
                cout << "------------------------\n";
            }
            current = current->next;
        }
    }
};

void songMenu(Playlist &playlist) {
    int choice;
    do {
        cout << "\n===== SONG MENU =====\n";
        cout << "1. Select Song\n";
        cout << "2. Update Song\n";
        cout << "3. Sort Playlist\n";
        cout << "4. Add Song to Queue\n";
        cout << "5. View Queue\n";
        cout << "6. Recently Played\n";
        cout << "7. Back\n";
        cout << "Enter choice: ";
        cin >> choice;
        if (choice == 1) {
            playlist.selectSong();
        } else if (choice == 2) {
            playlist.updateSong();
        } else if (choice == 3) {
            playlist.sortPlaylist();
        } else if (choice == 4) {
            int id;
            cout << "Enter Song ID: ";
            cin >> id;
            Song *song = playlist.findSong(id);
            if (song != nullptr) {
                cout << "Song: " << song->title << endl;
            } else {
                cout << "Song not found!\n";
            }
        } else if (choice == 5) {
            cout << "Queue option is available from the main menu.\n";
        } else if (choice == 6) {
            cout << "Recently played option is available from the main menu.\n";
        }
    } while (choice != 7);
}

int main() {
    Playlist playlist;
    PlayQueue playQueue;
    RecentlyPlayed recent;
    int choice;
    do {
        cout << "\n================ MUSIC PLAYLIST MANAGEMENT SYSTEM ================\n";
        cout << "1. View Playlist\n";
        cout << "2. Add Song\n";
        cout << "3. Delete Song\n";
        cout << "4. Search Song\n";
        cout << "5. Play Next Song\n";
        cout << "6. Play Previous Song\n";
        cout << "7. Album\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        if (choice == 1) {
            playlist.viewPlaylist();
        } else if (choice == 2) {
            playlist.addSong();
        } else if (choice == 3) {
            playlist.deleteSong();
        } else if (choice == 4) {
            playlist.searchSong();
        } else if (choice == 5) {
            playlist.playNextsong(recent);
        } else if (choice == 6) {
            playlist.playPreviousSong(recent);
        } else if (choice == 7) {
            playlist.showAlbums();
        } else if (choice == 8) {
            cout << "Thank you for using Music Playlist Management System!\n";
        } else {
            cout << "Invalid choice!\n";
        }
    } while (choice != 8);
    return 0;
}