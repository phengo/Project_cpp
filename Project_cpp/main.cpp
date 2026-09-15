#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

// --- 1. DATA MODEL & LINKED LIST NODE ---
struct Song {
    int id;
    string title;
    string artist;
    double duration; // in minutes
    Song* prev;
    Song* next;

    Song(int i, string t, string a, double d) 
        : id(i), title(t), artist(a), duration(d), prev(nullptr), next(nullptr) {}
};

// --- 2. CUSTOM STACK (History Tracking) ---
struct StackNode {
    Song* songData;
    StackNode* next;
    StackNode(Song* s) : songData(s), next(nullptr) {}
};

class HistoryStack {
private:
    StackNode* top;
public:
    HistoryStack() : top(nullptr) {}
    
    void push(Song* s) {
        StackNode* newNode = new StackNode(s);
        newNode->next = top;
        top = newNode;
    }

    Song* pop() {
        if (!top) return nullptr;
        StackNode* temp = top;
        Song* s = temp->songData;
        top = top->next;
        delete temp;
        return s;
    }

    void displayHistory() {
        if (!top) {
            cout << "No play history available.\n";
            return;
        }
        cout << "\n--- Recently Played History (Stack) ---\n";
        StackNode* curr = top;
        while (curr) {
            cout << "- " << curr->songData->title << " by " << curr->songData->artist << "\n";
            curr = curr->next;
        }
    }
};

// --- 3. CUSTOM QUEUE (Play Next Queue) ---
struct QueueNode {
    Song* songData;
    QueueNode* next;
    QueueNode(Song* s) : songData(s), next(nullptr) {}
};

class UpNextQueue {
private:
    QueueNode* front;
    QueueNode* rear;
public:
    UpNextQueue() : front(nullptr), rear(nullptr) {}

    void enqueue(Song* s) {
        QueueNode* newNode = new QueueNode(s);
        if (!rear) {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }

    Song* dequeue() {
        if (!front) return nullptr;
        QueueNode* temp = front;
        Song* s = temp->songData;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
        return s;
    }

    bool isEmpty() { return front == nullptr; }
};

// --- 4. DOUBLY LINKED LIST & PLAYLIST MANAGER ---
class Playlist {
private:
    Song* head;
    Song* tail;
    Song* current;
    HistoryStack history;
    UpNextQueue upNext;
    int songCount;

public:
    Playlist() : head(nullptr), tail(nullptr), current(nullptr), songCount(0) {}

    // CRUD: Create (Add Song)
    void addSong(int id, string title, string artist, double duration) {
        Song* newSong = new Song(id, title, artist, duration);
        if (!head) {
            head = tail = current = newSong;
        } else {
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }
        songCount++;
        cout << "Added: " << title << " by " << artist << "\n";
    }

    // CRUD: Read (Display Playlist)
    void displayPlaylist() {
        if (!head) {
            cout << "\nPlaylist is empty.\n";
            return;
        }
        cout << "\n" << left << setw(5) << "ID" << setw(25) << "Title" 
             << setw(20) << "Artist" << setw(10) << "Duration (m)" << "\n";
        cout << string(60, '-') << "\n";

        Song* temp = head;
        while (temp) {
            cout << left << setw(5) << temp->id 
                 << setw(25) << temp->title 
                 << setw(20) << temp->artist 
                 << setw(10) << fixed << setprecision(2) << temp->duration;
            if (temp == current) cout << " <-- [Currently Playing]";
            cout << "\n";
            temp = temp->next;
        }
    }

    // CRUD: Update
    void updateSong(int id, string newTitle, string newArtist, double newDuration) {
        Song* temp = head;
        while (temp) {
            if (temp->id == id) {
                temp->title = newTitle;
                temp->artist = newArtist;
                temp->duration = newDuration;
                cout << "Song ID " << id << " updated successfully.\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Song ID " << id << " not found.\n";
    }

    // CRUD: Delete
    void deleteSong(int id) {
        Song* temp = head;
        while (temp && temp->id != id) temp = temp->next;

        if (!temp) {
            cout << "Song ID " << id << " not found.\n";
            return;
        }

        if (temp == current) current = temp->next ? temp->next : temp->prev;
        if (temp->prev) temp->prev->next = temp->next;
        else head = temp->next;

        if (temp->next) temp->next->prev = temp->prev;
        else tail = temp->prev;

        delete temp;
        songCount--;
        cout << "Song ID " << id << " deleted successfully.\n";
    }

    // Player Controls
    void playCurrent() {
        if (!current) {
            cout << "Playlist is empty.\n";
            return;
        }
        cout << "\nNow Playing: " << current->title << " by " << current->artist << "\n";
        history.push(current);
    }

    void playNext() {
        if (!upNext.isEmpty()) {
            current = upNext.dequeue();
            playCurrent();
            return;
        }
        if (current && current->next) {
            current = current->next;
            playCurrent();
        } else {
            cout << "Reached the end of the playlist.\n";
        }
    }

    void playPrevious() {
        if (current && current->prev) {
            current = current->prev;
            playCurrent();
        } else {
            cout << "Already at the beginning of the playlist.\n";
        }
    }

    void addToQueue(int id) {
        Song* temp = head;
        while (temp && temp->id != id) temp = temp->next;
        if (temp) {
            upNext.enqueue(temp);
            cout << "Queued: " << temp->title << "\n";
        } else {
            cout << "Song ID not found.\n";
        }
    }

    void showHistory() { history.displayHistory(); }

    // SORTING ALGORITHM: Insertion Sort (Sorting DLL by Title)
    void sortByTitle() {
        if (!head || !head->next) return;

        Song* sorted = nullptr;
        Song* curr = head;

        while (curr) {
            Song* nextNode = curr->next;
            curr->prev = curr->next = nullptr;

            if (!sorted || sorted->title >= curr->title) {
                curr->next = sorted;
                if (sorted) sorted->prev = curr;
                sorted = curr;
            } else {
                Song* temp = sorted;
                while (temp->next && temp->next->title < curr->title) {
                    temp = temp->next;
                }
                curr->next = temp->next;
                if (temp->next) temp->next->prev = curr;
                temp->next = curr;
                curr->prev = temp;
            }
            curr = nextNode;
        }
        head = sorted;
        
        // Re-anchor tail
        Song* temp = head;
        while (temp && temp->next) temp = temp->next;
        tail = temp;

        cout << "Playlist sorted by Song Title using Insertion Sort.\n";
    }

    // PERSISTENCE: Save to CSV File
    void saveToCSV(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file for saving.\n";
            return;
        }
        Song* temp = head;
        while (temp) {
            file << temp->id << "," << temp->title << "," << temp->artist << "," << temp->duration << "\n";
            temp = temp->next;
        }
        file.close();
        cout << "Playlist saved to " << filename << " successfully.\n";
    }

    // PERSISTENCE: Load from CSV File
    void loadFromCSV(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) return;

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string idStr, title, artist, durStr;
            if (getline(ss, idStr, ',') && getline(ss, title, ',') &&
                getline(ss, artist, ',') && getline(ss, durStr, ',')) {
                addSong(stoi(idStr), title, artist, stod(durStr));
            }
        }
        file.close();
    }
};

// --- 5. MAIN MENU & DRIVER PROGRAM ---
int main() {
    Playlist myPlaylist;
    string filename = "playlist.csv";

    // Load saved songs if available
    myPlaylist.loadFromCSV(filename);

    int choice;
    do {
        cout << "\n========== MUSIC PLAYLIST MANAGER ==========\n"
             << "1. Display Playlist (Read)\n"
             << "2. Add Song (Create)\n"
             << "3. Edit Song (Update)\n"
             << "4. Delete Song (Delete)\n"
             << "5. Play Current Song\n"
             << "6. Play Next Song\n"
             << "7. Play Previous Song\n"
             << "8. Queue Song 'Up Next' (Queue)\n"
             << "9. View Song History (Stack)\n"
             << "10. Sort Playlist by Title (Insertion Sort)\n"
             << "11. Save Playlist to CSV\n"
             << "0. Exit\n"
             << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                myPlaylist.displayPlaylist();
                break;
            case 2: {
                int id; string title, artist; double duration;
                cout << "Enter ID: "; cin >> id;
                cin.ignore();
                cout << "Enter Title: "; getline(cin, title);
                cout << "Enter Artist: "; getline(cin, artist);
                cout << "Enter Duration: "; cin >> duration;
                myPlaylist.addSong(id, title, artist, duration);
                break;
            }
            case 3: {
                int id; string title, artist; double duration;
                cout << "Enter ID to update: "; cin >> id;
                cin.ignore();
                cout << "Enter New Title: "; getline(cin, title);
                cout << "Enter New Artist: "; getline(cin, artist);
                cout << "Enter New Duration: "; cin >> duration;
                myPlaylist.updateSong(id, title, artist, duration);
                break;
            }
            case 4: {
                int id;
                cout << "Enter Song ID to delete: "; cin >> id;
                myPlaylist.deleteSong(id);
                break;
            }
            case 5: myPlaylist.playCurrent(); break;
            case 6: myPlaylist.playNext(); break;
            case 7: myPlaylist.playPrevious(); break;
            case 8: {
                int id;
                cout << "Enter Song ID to Queue: "; cin >> id;
                myPlaylist.addToQueue(id);
                break;
            }
            case 9: myPlaylist.showHistory(); break;
            case 10: myPlaylist.sortByTitle(); break;
            case 11: myPlaylist.saveToCSV(filename); break;
            case 0:
                myPlaylist.saveToCSV(filename);
                cout << "Exiting system. Good luck with your presentation!\n";
                break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}