#include <iostream>
#include <string>
using namespace std;

// ==================== SONG ====================

struct Song
{
    int id;
    string title;
    string artist;
    string album;
    string duration;
};

// ==================== DOUBLY LINKED LIST NODE ====================

struct Node
{
    Song song;

    Node *next;
    Node *prev;
};

// ==================== PLAYLIST ====================

class Playlist
{
private:
    Node *head;
    Node *tail;

public:
    // Constructor
    Playlist()
    {
        head = NULL;
        tail = NULL;
    }

    // Destructor
    ~Playlist()
    {

        Node *current = head;

        while (current != NULL)
        {

            Node *temp = current;

            current = current->next;

            delete temp;
        }
    }

    // ==================== CREATE ====================

    void addSong()
    {

        Song song;

        cout << "\n===== ADD SONG =====\n";

        cout << "Enter ID: ";
        cin >> song.id;
        cin.ignore();

        cout << "Enter title: ";
        getline(cin, song.title);

        cout << "Enter artist: ";
        getline(cin, song.artist);

        cout << "Enter album: ";
        getline(cin, song.album);

        cout << "Enter duration (example 3:45): ";
        getline(cin, song.duration);

        Node *newNode = new Node;

        newNode->song = song;

        newNode->next = NULL;
        newNode->prev = NULL;

        // If playlist is empty
        if (head == NULL)
        {

            head = newNode;
            tail = newNode;
        }

        // If playlist already has songs
        else
        {

            tail->next = newNode;

            newNode->prev = tail;

            tail = newNode;
        }

        cout << "Song added successfully!\n";
    }

    // ==================== READ ====================

    void displaySongs()
    {

        cout << "\n===== PLAYLIST =====\n";

        if (head == NULL)
        {

            cout << "Playlist is empty.\n";
            return;
        }

        Node *current = head;

        while (current != NULL)
        {

            cout << "ID: " << current->song.id << endl;
            cout << "Title: " << current->song.title << endl;
            cout << "Artist: " << current->song.artist << endl;
            cout << "Album: " << current->song.album << endl;
            cout << "Duration: " << current->song.duration << endl;

            cout << "-------------------------\n";

            current = current->next;
        }
    }

    // ==================== SEARCH ====================

    void searchSong()
    {

        int id;

        cout << "\n===== SEARCH SONG =====\n";

        cout << "Enter song ID: ";
        cin >> id;

        Node *current = head;

        while (current != NULL)
        {

            if (current->song.id == id)
            {

                cout << "\nSong found!\n";

                cout << "ID: " << current->song.id << endl;
                cout << "Title: " << current->song.title << endl;
                cout << "Artist: " << current->song.artist << endl;
                cout << "Album: " << current->song.album << endl;
                cout << "Duration: " << current->song.duration << endl;

                return;
            }

            current = current->next;
        }

        cout << "Song not found.\n";
    }

    // ==================== UPDATE ====================

    void updateSong()
    {

        int id;

        cout << "\n===== UPDATE SONG =====\n";

        cout << "Enter song ID: ";
        cin >> id;

        cin.ignore();

        Node *current = head;

        while (current != NULL)
        {

            if (current->song.id == id)
            {

                cout << "Enter new title: ";
                getline(cin, current->song.title);

                cout << "Enter new artist: ";
                getline(cin, current->song.artist);

                cout << "Enter new album: ";
                getline(cin, current->song.album);

                cout << "Enter new duration: ";
                getline(cin, current->song.duration);

                cout << "Song updated successfully!\n";

                return;
            }

            current = current->next;
        }

        cout << "Song not found.\n";
    }

    // ==================== DELETE ====================

    void deleteSong()
    {

        int id;

        cout << "\n===== DELETE SONG =====\n";

        cout << "Enter song ID: ";
        cin >> id;

        Node *current = head;

        while (current != NULL)
        {

            if (current->song.id == id)
            {

                // If deleting the first node
                if (current == head)
                {

                    head = current->next;

                    if (head != NULL)
                    {
                        head->prev = NULL;
                    }
                    else
                    {
                        // current was also the tail (list is now empty)
                        tail = NULL;
                    }
                }

                // If deleting the last node (and not the head)
                else if (current == tail)
                {

                    tail = current->prev;

                    tail->next = NULL;
                }

                // If deleting a middle node
                else
                {

                    current->prev->next = current->next;

                    current->next->prev = current->prev;
                }

                delete current;

                cout << "Song deleted successfully!\n";

                return;
            }

            current = current->next;
        }

        cout << "Song not found.\n";
    }

    // ==================== BUBBLE SORT ====================

    void sortSongs()
    {

        if (head == NULL || head->next == NULL)
        {

            cout << "Not enough songs to sort.\n";

            return;
        }

        bool swapped;

        do
        {

            swapped = false;

            Node *current = head;

            while (current->next != NULL)
            {

                if (current->song.title > current->next->song.title)
                {

                    Song temp = current->song;

                    current->song = current->next->song;

                    current->next->song = temp;

                    swapped = true;
                }

                current = current->next;
            }

        } while (swapped);

        cout << "Playlist sorted by title successfully!\n";
    }

    // ==================== FIND SONG ====================

    Song *findSong(int id)
    {

        Node *current = head;

        while (current != NULL)
        {

            if (current->song.id == id)
            {

                return &current->song;
            }

            current = current->next;
        }

        return NULL;
    }

    // ==================== FORWARD ====================

    void displayForward()
    {

        cout << "\n===== FORWARD =====\n";

        if (head == NULL)
        {

            cout << "Playlist is empty.\n";

            return;
        }

        Node *current = head;

        while (current != NULL)
        {

            cout << current->song.title
                 << " - "
                 << current->song.artist
                 << endl;

            current = current->next;
        }
    }

    // ==================== BACKWARD ====================

    void displayBackward()
    {

        cout << "\n===== BACKWARD =====\n";

        if (tail == NULL)
        {

            cout << "Playlist is empty.\n";

            return;
        }

        Node *current = tail;

        while (current != NULL)
        {

            cout << current->song.title
                 << " - "
                 << current->song.artist
                 << endl;

            current = current->prev;
        }
    }
};

// ==================== QUEUE ====================

struct QueueNode
{

    Song song;

    QueueNode *next;
};

class PlayQueue
{

private:
    QueueNode *front;
    QueueNode *rear;

public:
    // Constructor
    PlayQueue()
    {

        front = NULL;
        rear = NULL;
    }

    // Destructor
    ~PlayQueue()
    {

        while (front != NULL)
        {

            QueueNode *temp = front;

            front = front->next;

            delete temp;
        }
    }

    // Add song to queue
    void enqueue(Song song)
    {

        QueueNode *newNode = new QueueNode;

        newNode->song = song;

        newNode->next = NULL;

        if (rear == NULL)
        {

            front = newNode;

            rear = newNode;
        }

        else
        {

            rear->next = newNode;

            rear = newNode;
        }

        cout << "Song added to play queue.\n";
    }

    // Play next song
    Song *dequeue()
    {

        if (front == NULL)
        {

            cout << "Play queue is empty.\n";

            return NULL;
        }

        QueueNode *temp = front;

        Song *playedSong = new Song;

        *playedSong = temp->song;

        front = front->next;

        if (front == NULL)
        {

            rear = NULL;
        }

        delete temp;

        return playedSong;
    }

    // Display queue
    void displayQueue()
    {

        cout << "\n===== PLAY QUEUE =====\n";

        if (front == NULL)
        {

            cout << "Queue is empty.\n";

            return;
        }

        QueueNode *current = front;

        while (current != NULL)
        {

            cout << current->song.title
                 << " - "
                 << current->song.artist
                 << endl;

            current = current->next;
        }
    }
};

// ==================== STACK ====================

struct StackNode
{

    Song song;

    StackNode *next;
};

class RecentlyPlayed
{

private:
    StackNode *top;

public:
    // Constructor
    RecentlyPlayed()
    {

        top = NULL;
    }

    // Destructor
    ~RecentlyPlayed()
    {

        while (top != NULL)
        {

            StackNode *temp = top;

            top = top->next;

            delete temp;
        }
    }

    // Push
    void push(Song song)
    {

        StackNode *newNode = new StackNode;
        

        newNode->song = song;

        newNode->next = top;

        top = newNode;
    }

    // Pop
    void pop()
    {

        if (top == NULL)
        {

            cout << "No recently played songs.\n";

            return;
        }

        StackNode *temp = top;

        cout << "Removed: "
             << temp->song.title
             << endl;

        top = top->next;

        delete temp;
    }

    // Display
    void display()
    {

        cout << "\n===== RECENTLY PLAYED =====\n";

        if (top == NULL)
        {

            cout << "No recently played songs.\n";

            return;
        }

        StackNode *current = top;

        while (current != NULL)
        {

            cout << current->song.title
                 << " - "
                 << current->song.artist
                 << endl;

            current = current->next;
        }
    }
};

// ==================== MAIN ====================

int main()
{

    Playlist playlist;

    PlayQueue playQueue;

    RecentlyPlayed recentlyPlayed;

    int choice;

    do
    {

        cout << "\n====================================\n";
        cout << "     MUSIC PLAYLIST MANAGEMENT\n";
        cout << "====================================\n";

        cout << "1. Add Song\n";
        cout << "2. View Playlist\n";
        cout << "3. Search Song\n";
        cout << "4. Update Song\n";
        cout << "5. Delete Song\n";
        cout << "6. Sort Playlist\n";
        cout << "7. View Playlist Forward\n";
        cout << "8. View Playlist Backward\n";
        cout << "9. Add Song to Play Queue\n";
        cout << "10. Play Next Song\n";
        cout << "11. View Play Queue\n";
        cout << "12. View Recently Played\n";
        cout << "13. Remove Recent Song\n";
        cout << "0. Exit\n";

        cout << "\nEnter your choice: ";

        cin >> choice;

        switch (choice)
        {

        case 1:

            playlist.addSong();

            break;

        case 2:

            playlist.displaySongs();

            break;

        case 3:

            playlist.searchSong();

            break;

        case 4:

            playlist.updateSong();

            break;

        case 5:

            playlist.deleteSong();

            break;

        case 6:

            playlist.sortSongs();

            break;

        case 7:

            playlist.displayForward();

            break;

        case 8:

            playlist.displayBackward();

            break;

        case 9:
        {
            int id;

            cout << "\nEnter song ID to add to queue: ";

            cin >> id;

            Song *song = playlist.findSong(id);

            if (song != NULL)
            {

                playQueue.enqueue(*song);
            }

            else
            {

                cout << "Song not found.\n";
            }

            break;
        }

        case 10:
        {
            Song *song = playQueue.dequeue();

            if (song != NULL)
            {

                cout << "\nNow Playing: "
                     << song->title
                     << " - "
                     << song->artist
                     << endl;

                recentlyPlayed.push(*song);

                delete song;
            }

            break;
        }

        case 11:

            playQueue.displayQueue();

            break;

        case 12:

            recentlyPlayed.display();

            break;

        case 13:

            recentlyPlayed.pop();

            break;

        case 0:

            cout << "\nThank you for using Music Playlist Management System!\n";

            break;

        default:

            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}