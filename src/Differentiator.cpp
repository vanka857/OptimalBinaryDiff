#include "Differentiator.hpp"

namespace OBD {

Differentiator::Differentiator(const OBD::File & file1, const OBD::File & file2) : file1_(file1), file2_(file2) {
    content1 = std::string(file1_.GetContent());
    content2 = std::string(file2_.GetContent());
}

void Differentiator::CalcDiff() {

}

std::vector<int> Differentiator::NWScore(std::vector<char>::iterator & begin1, std::vector<char>::iterator & end1,
                                         std::vector<char>::iterator & begin2, std::vector<char>::iterator & end2) {

    const static int INS = -8;
    const static int DEL = -8;

    std::vector<std::vector<int>> score(2);
    score[0].resize(end2 - begin2);
    score[1].resize(end2 - begin2);

    score[0][0] = 0;

    for (auto j = 1 + begin2; j != end2; ++j) {
        score[0][j - begin2] = score[0][j - begin2 - 1] + INS;
    }
    for (auto i = 1 + begin1; i != end1; ++i) {
        score[1][0] = score[0][0] + DEL;
        for (auto j = 1 + begin2; j != end2; ++i) {
            auto scoreSub = score[0][j - begin2 - 1] + (*i - *j);
            auto scoreDel = score[0][j - begin2] + DEL;
            auto scoreIns = score[1][j - begin2 - 1] + INS;
            score[1][j - begin2] = std::max({scoreSub, scoreDel, scoreIns});
        }
        score[0] = score[1];
    }

    return std::move(score[1]);
}

std::pair<std::string, std::string>
Differentiator::Hirschberg(std::vector<char>::iterator & begin1, std::vector<char>::iterator & end1,
                           std::vector<char>::iterator & begin2, std::vector<char>::iterator & end2) {
    std::string Z = "";
    std::string W = "";

    if (file1_.binary_size() == 0) {
        for (size_t i = 1; i < file2_.binary_size(); ++i) {
            Z += '-';
            W += std::to_string(int(file2_.LocateBinary(i)));
        }
    } else if (file2_.binary_size() == 0) {
        for (size_t i = 1; i < file1_.binary_size(); ++i) {
            Z += std::to_string(int(file1_.LocateBinary(i)));
            W += '-';
        }
    } else if (file2_.binary_size() == 1 || file1_.binary_size() == 1) {
        //
    } else {
        auto mid1 = begin1 + (begin1 - end1) / 2;

        auto ScoreL = NWScore(begin1, mid1, begin2, end2);
        auto ScoreR = NWScore(std::make_reverse_iterator(mid1 + 1), std::reverse_iterator(end1),
                              std::reverse_iterator(begin2), std::reverse_iterator(end2));

        auto sc = ScoreL;
        for (size_t i = 0; i < ScoreL.size(); ++i) {
            sc[i] += ScoreR[ScoreL.size() - 1 - i];
        }

        auto mid2 = begin2 + static_cast<int>(std::max_element(sc.begin(), sc.end()) - sc.begin());

        auto [z1, w1] = Hirschberg(begin1, mid1, begin2, mid2);
        auto [z2, w2] = Hirschberg(mid1 + 1, end1, mid2 + 1, end2);
        Z = z1 + z2;
        W = w1 + w2;
    }
    return {Z, W};
}

}
