#include <iostream>
#include <string>
using namespace std;

struct ResearchPaper {
    string title;
    string abstract;
    string keywords[5];  // Giới hạn 5 từ khóa
};

bool searchInKeywords(string keywords[], int keywordCount, string query) {
    for (int i = 0; i < keywordCount; i++) {
        if (keywords[i] == query) {
            return true;
        }
    }
    return false;
}

void searchPapers(ResearchPaper papers[], int n, string query) {
    for (int i = 0; i < n; i++) {
        if (papers[i].title.find(query) != string::npos || papers[i].abstract.find(query) != string::npos ||
            searchInKeywords(papers[i].keywords, 5, query)) {
            cout << "Bài báo: " << papers[i].title << ", Tóm tắt: " << papers[i].abstract << endl;
        }
    }
}

int main() {
    ResearchPaper papers[] = {
        {"AI in Healthcare", "Ứng dụng AI trong y tế", {"AI", "Healthcare", "Machine Learning", "", ""}},
        {"Machine Learning Basics", "Cơ bản về máy học", {"Machine Learning", "AI", "", "", ""}}
    };
    int n = sizeof(papers) / sizeof(papers[0]);
    string query = "AI";
    searchPapers(papers, n, query);
    return 0;
}
