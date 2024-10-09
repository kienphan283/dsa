#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

class MusicPlayer {
private:
    list<string> playlist;
    unordered_map<string, list<string>::iterator> songMap;
    list<string>::iterator currentSong = playlist.end();

public:
    void addSong(const string& songName) {
        playlist.push_back(songName);
        songMap[songName] = --playlist.end();
        if (playlist.size() == 1) currentSong = playlist.begin();
    }

    void playNext() {
        if (playlist.empty()) return;
        currentSong = (next(currentSong) == playlist.end()) ? playlist.begin() : next(currentSong);
    }

    void playPrev() {
        if (playlist.empty()) return;
        currentSong = (currentSong == playlist.begin()) ? --playlist.end() : prev(currentSong);
    }

    void removeSong(const string& songName) {
        auto it = songMap.find(songName);
        if (it == songMap.end()) return;
        if (currentSong == it->second) {
            currentSong = (next(currentSong) == playlist.end()) ? playlist.begin() : next(currentSong);
        }
        playlist.erase(it->second);
        songMap.erase(it);
    }

    void display() const {
        for (const auto& song : playlist) cout << song << " ";
        cout << endl;
    }
};

int main() {
    int n;
    cin >> n;
    MusicPlayer player;

    while (n--) {
        string command, songName;
        cin >> command;
        if (command == "ADD") {
            cin >> songName;
            player.addSong(songName);
        } else if (command == "NEXT") {
            player.playNext();
        } else if (command == "PREV") {
            player.playPrev();
        } else if (command == "REMOVE") {
            cin >> songName;
            player.removeSong(songName);
        } else if (command == "DISPLAY") {
            player.display();
        }
    }
    return 0;
}
