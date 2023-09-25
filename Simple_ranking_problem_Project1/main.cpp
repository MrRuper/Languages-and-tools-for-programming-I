#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <regex>
#include <algorithm>

// This map will hold:
// number_of_the_song -> number_of_points.
// It will be refreshed after each NEW_MAX command.
std::map<int, int> current_ranking;

// This map will hold:
// number_of_the_song -> total_number_of_points.
// It will hold the total number of achieved points
// for every song.
std::map<int, int> history_ranking;

// This set will hold numbers of
// songs that are removed.
std::set<int> removed_songs;

// This will hold the previous NEW_MAX result.
// Index is a place in ranking (maximum 7)
// and value is the number of song.
std::vector<int> remember_last_NEW_MAX;

// This will hold the previous TOP result.
std::vector<int> remember_last_TOP;

long long int MAX = -1;

bool sort_by_sec_desc(const std::pair<int,int> &a, const std::pair<int,int> &b) {
        return a.second > b.second;
}

// Fix: the higher position takes song with less number.
void NEW_MAX_command(const int NEW_MAX) {
    std::vector<std::pair<int,int>> song_score(current_ranking.size());

    int index = 0;

    for (auto i : current_ranking) {
        song_score[index] = {i.first, i.second};
        index++;
    }

    // Firstly sort with respect to the song_number,
    // secondly sort with respect to the number_of_points.
    // This will ensure that if two songs x, y have the same number of
    // points, min{x,y} will be before max{x,y}.
    std::sort(song_score.begin(), song_score.end());
    std::sort(song_score.begin(), song_score.end(), sort_by_sec_desc);

    std::vector<int> seven_best_songs(std::min((uint64_t) 7, song_score.size()));

    for (int i = 0; i < seven_best_songs.size(); i++) {
        seven_best_songs[i] = song_score[i].first;
    }

    for (int i = 0; i < seven_best_songs.size(); i++) {
        int current_song_number = song_score[i].first;

        bool song_found_in_last_ranked = false;

        for (int j = 0; j < remember_last_NEW_MAX.size(); j++) {
            if (remember_last_NEW_MAX[j] == current_song_number) {
                song_found_in_last_ranked = true;

                // Change of position = i - j.
                std::cout << current_song_number << " " << j - i << std::endl;
            }
        }

        if (!song_found_in_last_ranked) {
            std::cout << current_song_number << " -" << std::endl;
        }

        // Update TOP result.
        history_ranking[current_song_number] += 7 - i;
    }

    // Update removed_song.
    for (int i = 0; i < remember_last_NEW_MAX.size(); i++) {
        int song_number = remember_last_NEW_MAX[i];
        bool passed_to_next_ranking = false;

        for (int j = 0; j < seven_best_songs.size(); j++) {
            if (song_number == seven_best_songs[j]) {
                passed_to_next_ranking = true;
            }
        }

        if (!passed_to_next_ranking) {
            removed_songs.insert(song_number);
        }
    }

    // Clear all possible stuff.
    remember_last_NEW_MAX.clear();
    current_ranking.clear();
    song_score.clear();

    // Update global variables.
    remember_last_NEW_MAX = seven_best_songs;
    MAX = NEW_MAX;
}

void TOP_command() {
    std::vector<std::pair<int,int>> song_general_score(history_ranking.size());

    int counter = 0;

    for (auto i : history_ranking) {
        song_general_score[counter] = i;
        counter++;
    }

    std::sort(song_general_score.begin(), song_general_score.end());
    std::sort(song_general_score.begin(), song_general_score.end(), sort_by_sec_desc);

    std::vector<int> seven_best_for_TOP(std::min((uint64_t) 7, song_general_score.size()));

    for (int i = 0; i < seven_best_for_TOP.size(); i++) {
        int current_song_number = song_general_score[i].first;
        bool appeared_previously = false;

        seven_best_for_TOP[i] = current_song_number;
        counter = 0;

        for (auto j : remember_last_TOP) {
            if (j == current_song_number) {
                appeared_previously = true;
                std::cout << current_song_number << " " << counter - i << std::endl;
            }

            counter++;
        }

        if (!appeared_previously) {
            std::cout << current_song_number << " -" << std::endl;
        }
    }

    // Clear all possible stuff.
    song_general_score.clear();
    remember_last_TOP.clear();

    remember_last_TOP = seven_best_for_TOP;
}

void print_error(std::string& invalid_string, uint64_t line_number) {
    std::cerr << "Error in line " << line_number << ": " << invalid_string << std::endl;
}

bool invalid_song(long long int song_number) {
    if (removed_songs.find(song_number) != removed_songs.end() ||
        song_number > 99999999 ||
        song_number > MAX || song_number < 1) {
        return true;
    }

    return false;
}

void process_vote(std::string& line, uint64_t line_number) {
    std::regex pattern("[^\\s]+");
    std::set<int> check_different;
    std::vector<int> vote;
    long long int song;
    int NEW_MAX;

    auto words_begin = std::sregex_iterator(line.begin(),
                                            line.end(),
                                            pattern);
    auto words_end = std::sregex_iterator();

    long long int length_of_word = std::distance(words_begin, words_end);

    if (length_of_word == 1) {
        if (words_begin->str() == "TOP") {
            TOP_command();

            return;
        }
        else {
            try {
                song = std::stoi(words_begin->str());
            }
            catch (std::invalid_argument const& invalid) {
                print_error(line, line_number);

                return;
            }

            if (invalid_song(song)) {
                    print_error(line, line_number);

                    return;
            }
            else {
                vote.push_back(song);
            }
        }
    }
    else if (length_of_word == 2) {
        if (words_begin->str() == "NEW") {
            auto next_word = words_begin;
            next_word++;

            try {
                NEW_MAX = std::stoi(next_word->str());
            }
            catch (std::invalid_argument const& invalid) {
                print_error(line, line_number);

                return;
            }

            if (NEW_MAX < 1 || NEW_MAX < MAX) {
                print_error(line, line_number);

                return;
            }
            else {
                NEW_MAX_command(NEW_MAX);

                return;
            }
        }
        else {
            long long int song1, song2;
            auto next = words_begin;

            next++;

            try {
                song1 = std::stoi(words_begin->str());
                song2 = std::stoi(next->str());
            }
            catch (std::invalid_argument const& invalid) {
                print_error(line, line_number);

                return;
            }

            if (song1 == song2 ||
                invalid_song(song1) ||
                invalid_song(song2)) {
                print_error(line, line_number);

                return;
            }
            else {
                vote.push_back(song1);
                vote.push_back(song2);
            }
        }
    }
    else {
        for (std::sregex_iterator i = words_begin; i != words_end; i++) {
            try {
                song = std::stoi(i->str());
            }
            catch (std::invalid_argument const& argument) {
                print_error(line, line_number);
            }

            if (invalid_song(song) ||
                check_different.find(song) != check_different.end()) {
                print_error(line, line_number);
                check_different.clear();
                vote.clear();

                return;
            }

            check_different.insert(song);
            vote.push_back(song);
        }
    }

    for (auto z : vote) {
        current_ranking[z]++;
    }

    vote.clear();
    check_different.clear();
}


int main() {
    std::string line;
    uint64_t line_number = 0;

    while (std::getline(std::cin, line)) {
        line_number++;
        process_vote(line, line_number);
    }

    return 0;
}
