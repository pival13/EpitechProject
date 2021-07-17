/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019 [WSL: Ubuntu]
** File description:
** automatizedTest
*/

#include "../Trantorian.hpp"

class TestTrantorian : public Trantorian {
    public:
        TestTrantorian(const std::string &teamName) : Trantorian(teamName) { _pos = pos_t({0,0}); }
        ~TestTrantorian() = default;

        void launch()
        {
            testActionToReach({0,0}, {0,0});
            testActionToReach({0,0}, {0,1});
            testActionToReach({0,0}, {1,0});
            testActionToReach({0,0}, {-1,0});
            testActionToReach({0,0}, {0,-1});
            testActionToReach({0,0}, {1,1});
            testActionToReach({0,0}, {-1,1});
            testActionToReach({0,0}, {-1,-1});
            testActionToReach({0,0}, {1,-1});
            testActionToReach({0,0}, {19,20});
        }

    private:
        void testActionToReach(pos_t p1, pos_t p2)
        {
            _pos = p1;
            std::cout << "Current pos: " << _pos << ", target pos: " << p2 << ", distance: " << actionToReach(p2) << std::endl;
        }
};

std::string connectionHost = "www.google.com";
std::string connectionPort = "80";

int main()
{
    TestTrantorian tester("Team1");

    tester.launch();
}