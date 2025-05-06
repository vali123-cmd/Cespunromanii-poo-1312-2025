std::ostream& operator<<(std::ostream& os, const Round& q) {
    os << "Round ID: " << q.get_round_id() << '\n';
    os << "Answers Given:\n";
    if (!q.answers_given.empty()) {
        for (const auto& answer : q.answers_given) {
            os << "- " << answer.first << ": " << answer.second << '\n';
        }
    } else {
        os << "No answers given yet.\n";
    }
    return os;
}
