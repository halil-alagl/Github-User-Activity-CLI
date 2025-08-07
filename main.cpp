#include <iostream>
#include <fstream>
#include <cpr/cpr.h>
#include <json/json.h>
#include <json/value.h>
#include <unordered_map>
std::unordered_map<std::string, std::string> eventMessages = {
    {"CreateEvent", "- Created a repository at "},
    {"IssueCommentEvent", "- Commented an issue at "},
    {"IssuesEvent", "- Created an issue at "},
    {"CommitCommentEvent", "- Commented on a commit at "},
    {"DeleteEvent", "- Deleted something at "},
    {"ForkEvent", "- Forked repository "},
    {"GollumEvent", "- Updated a wiki in "},
    {"MemberEvent", "- Added a member to "},
    {"PublicEvent", "- Made repository public: "},
    {"PullRequestEvent", "- Opened a pull request in "},
    {"PullRequestReviewEvent", "- Reviewed a pull request in "},
    {"PullRequestReviewCommentEvent", "- Commented on a pull request review in "},
    {"PullRequestReviewThreadEvent", "- Participated in a pull request review thread in "},
    {"PushEvent", "- Pushed to "},
    {"ReleaseEvent", "- Published a release in "},
    {"SponsorshipEvent", "- Sponsored or received sponsorship in "},
    {"WatchEvent", "- Starred "}
};

int main(int argc, char* argv[]) {
    std::string username;
    if (argv[1])
        username = argv[1];
    else
        do
        {
            std::cout << "Please enter a Github username\n-> ";
            std::cin >> username;
        } while (username.empty());

    std::stringstream ss;

    ss << "https://api.github.com/users/" << username << "/events";
    std::string ghubUrl = ss.str();
    std::cout << ghubUrl << '\n';
    cpr::Response response = cpr::Get(cpr::Url{ ghubUrl });
    const std::string fileName = username + "_activity.json";
    std::ofstream o(fileName);
    o << response.text << std::endl;
    std::ifstream activity_file(fileName, std::ifstream::binary);
    Json::Value val;
    activity_file >> val;
    int count = 0;
    std::cout << val[5]["type"].asString() << '\n';
    do {
        if (!val[count]["type"].asString().empty()) {
            count++;
            continue;
        }
        break;
    } while (true);

    for (int i = 0; i < count; i++) {
        std::string message = val[i]["type"].asString();
        auto it = eventMessages.find(message);
        if (it != eventMessages.end()) {
            std::cout << it->second << val[i]["repo"]["name"] << '\n';
        }
    }
    return 0;
}