//
// Created by Rajendra Hathwar on 2020-01-18.
//

#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <stdlib.h>
#include "gtest/gtest.h"
#include "betterstatemachine.h"
#include "robot.h"
#include "limits.h"
#include <vector>


using std::string;
using std::vector;
using namespace elma;
using namespace std::chrono;
using nlohmann::json; 

#define EPSILON DBL_EPSILON*10.0 // double tolerance
#define DBL_PRECISION 0.0001
#define Q1POINTS 100.0
#define Q2POINTS 100.0
#define NUM_QUESTIONS 2 // overestimated number of questions
#define GTEST_COUT_GRADE std::cerr       << "[    GRADE ] "

/*
 * This is the base test class for all of the methods.
 *
 * All other tests inherit from this base class. It
 * contains several methods for building vector matrices,
 * random matrices, etc. for testing purposes.
 *
 * You can also see some file creation stuff that is relevant for
 * the homework.
 */
class BaseTest : public ::testing::Test {
protected:

    /*!
     * Compare two doubles, with relaxed tolerances
     * @param a
     * @param b
     * @return
     */
    bool compare_dbl(double a, double b) {
        if (fabs(a - b) < EPSILON) {
            return true;
        }
        return false;
    }

    /*!
     * Creates a random double.
     *
     * @param min
     * @param max
     * @return
     */
    double random_dbl(double min, double max) {
        double range = (max - min);
        double div = RAND_MAX / range;
        return min + (rand() / div);
    }

    /*!
     * Random integer between min and max
     * @param min
     * @param max
     * @return
     */
    int random_int(int min, int max) {
        if (max == 0) {
            return 0;
        }
        return rand() % max + min;
    }

    /*!
     * Creates a random double vector.
     *
     * @param size number of doubles in the vector
     * @param min minimum double
     * @param max maximum double
     * @return vector of doubles
     */
     vector<int> int_vector(int size, int min, int max) {
         vector<int> v;
         v.resize(size);
         for (int i = 0; i < size; i++) {
             v[i] = random_int(min, max);
         }
         return v;
     }

    /*!
     * Creates a random int vector.
     *
     * @param size number of doubles in the vector
     * @param min minimum double
     * @param max maximum double
     * @return vector of doubles
     */
    vector<double> dbl_vector(int size, double min, double max) {
        vector<double> v;
        v.resize(size);
        for (int i = 0; i < size; i++) {
            v[i] = random_dbl(min, max);
        }
        return v;
    }

     /*!
    * Create a random vector<vector<double>> matrix of doubles.
    *
    * @param r
    * @param c
    * @param mn
    * @param mx
    * @returnFc
    */
    vector<vector<double>> dbl_matrix(int r, int c, double mn, double mx) {
        vector<vector<double>> x;
        x.resize(r);
        for (int i = 0; i < r; i++) {
            x[i] = dbl_vector(c, mn, mx);
        }
        return x;
    }

     /*!
    * Create a random vector<vector<int>> matrix of ints.
    *
    * @param r
    * @param c
    * @param mn
    * @param mx
    * @return
    */
    vector<vector<int>> int_matrix(int r, int c, int mn, int mx) {
        vector<vector<int>> x;
        x.resize(r);
        for (int i = 0; i < r; i++) {
            x[i] = int_vector(c, mn, mx);
        }
        return x;
    }

     /*!
      * Print double vector contents
      */
      void print_vector(vector<double> &v) {
          std::cout << "[ ";
          vector<double>::iterator i;
          for (i = v.begin(); i != v.end(); i++) {
              std::cout << (*i) << " ";
          }
          std::cout << "]" << std::endl;
      }

      /*!
      * Print double vector contents
      */
      void print_vector(vector<int> &v) {
          std::cout << "[ ";
          vector<int>::iterator i;
          for (i = v.begin(); i != v.end(); i++) {
              std::cout << (*i) << " ";
          }
          std::cout << "]" << std::endl;
      }

      /*!
      * Print double vector contents
      */
      void print_vector(vector<string> &v) {
          std::cout << "[ ";
          vector<string>::iterator i;
          for (i = v.begin(); i != v.end(); i++) {
              std::cout << (*i) << " ";
          }
          std::cout << "]" << std::endl;
      }
};

/*
 * Define the base test classes for each of the questions.
 *
 * Each question should inherit from the main Question base,
 * which holds three static vectors (number of tests, number of
 * passing tests, total point value). Each inherited class
 * should get its own unique integer id. To get the number of tests,
 * number of passing tests, or total point values for a question,
 * just access the static vectors with the corresponding unique
 * int id.
 *
 * The individual weights for each question can be adjusted via
 * the "totals" static vector. The number of tests and number
 * of passing tests are computed automatically.
 *
 * To get the total grade, call "grade()". To get a grade break down
 * of each question, call "question_grades()".
 */

class Question : public BaseTest {
public:
    static vector<int> num_tests;
    static vector<int> num_passed;
    static vector<double> totals;

protected:
    int total_points;
    int id = -1;

    Question() {
        num_tests.resize(NUM_QUESTIONS);
        num_passed.resize(NUM_QUESTIONS);
        totals.resize(NUM_QUESTIONS);
    }

    virtual vector<double> question_grades() {
        vector<double> grade;
        grade.resize(NUM_QUESTIONS);
        for (int i = 0; i < NUM_QUESTIONS; i++) {
            if (totals[i] > 0) {
                grade[i] = (double) num_passed[i]/num_tests[i] * totals[i];
            }
        }
        return grade;
    }

    virtual double grade() {

        double t, v;
        for (int i = 0; i < NUM_QUESTIONS; i++) {
            if (totals[i] > 0) {
                v += (double) num_passed[i]/num_tests[i] * totals[i];
                t += totals[i];
            }
        }
        return v/t;
    }

    void print_grade() {
        vector<double> q = question_grades();
        GTEST_COUT_GRADE << grade() * 100.0 << "%" << std::endl;
        GTEST_COUT_GRADE << "Question breakdown: " << std::endl;
        std::cout << grade() * 100.0 << std::endl;
        std::cout << "Question breakdown: " << std::endl;
        print_vector(q);
    }

    virtual void TearDown() {
        if (!HasFailure()) {
            num_passed[id]++;
        }
        print_grade();
    }
};

vector<int> Question::num_tests;
vector<int> Question::num_passed;
vector<double> Question::totals;
// get number of questions

class Question1 : public Question {
protected:
    Question1() {
        id = 0;
        totals[id] = Q1POINTS;
        num_tests[id]++;
    }
};

class Question2 : public Question {
protected:
    Question2() {
        id = 1;
        totals[id] = Q2POINTS;
        num_tests[id]++;
    }
};

/*
 * Question 1: robot *************************************************
 */

class RobotTests : public Question1,
                    public ::testing::WithParamInterface<std::pair<vector<string>, vector<string>>> {
};

vector <std::pair<vector<string>, vector<string>>> robotTestVec = {
    { {"intruder detected", "proximity warning", "battery full"}, {"Make Noise", "Evade", "Evade"}},
    { {"battery low", "battery low", "found recharge station", "reset"}, {"Find Recharge Station","Find Recharge Station","Recharge","Recharge"}},
    { {"intruder detected", "found recharge station", "proximity warning"}, {"Make Noise", "Make Noise", "Evade"}},
    { {"battery low", "proximity warning", "intruder detected", "reset"}, {"Find Recharge Station","Find Recharge Station","Find Recharge Station","Find Recharge Station"}},
    { {"proximity warning", "found recharge station", "intruder detected", "reset"}, {"Wander", "Wander", "Make Noise", "Wander"}}
    }; //event, next state

TEST_P(RobotTests, StateMachineTest) {
    Robot robot("What a very nice robot.");

    std::pair<vector<string>, vector<string>> my_pair = GetParam();
    vector<string> event = std::get<0>(my_pair);
    vector<string> next_state = std::get<1>(my_pair);
    Manager m;
    m.schedule(robot, 10_ms)
    .init()
    .start();

    EXPECT_EQ(robot.current().name(), "Wander");
    for(int i = 0; i < event.size(); i++)
    {
        m.emit(Event(event[i]));
        EXPECT_EQ(robot.current().name(), next_state[i]);
    }
}


//Param A random name, Param B test class and Param C list of inputs
INSTANTIATE_TEST_CASE_P(RobotTests,
        RobotTests,
        testing::ValuesIn(robotTestVec)
);

/*
 * Question 2: Better State Machine *************************************************
 */

class BetterStateMachineTests : public Question2 {
};

TEST_F(BetterStateMachineTests, ToggleSwitchTest) {
    Mode off("off"), on("on");
    BetterStateMachine fsm("toggle switch");

    fsm.set_initial(off)
    .set_propagate(false)
    .add_transition("switch", off, on)
    .add_transition("switch", on, off);

    json j = fsm.to_json();
    ASSERT_EQ(j["name"], "toggle switch");
    ASSERT_EQ(j["states"].size(), 2);
};

//Param A name the test class, Param B good name for what the tests represent
TEST_F(BetterStateMachineTests, RobotTest) {
    Mode wander("Wander"), make_noise("Make Noise"), evade("Evade");
    Mode find_recharge_station("Find Recharge Station"), recharge("Recharge");
    BetterStateMachine fsm("Cool Robot");

    fsm.set_initial(wander)
    .add_transition("battery low", wander, find_recharge_station)
    .add_transition("intruder detected", wander, make_noise)
    .add_transition("found recharge station", find_recharge_station, recharge)
    .add_transition("battery full", recharge, wander)
    .add_transition("reset", make_noise, wander)
    .add_transition("proximity warning", make_noise, evade)
    .add_transition("reset", evade, make_noise)
    .add_transition("battery low", evade, find_recharge_station);

    json j = fsm.to_json();

    //std::cout << j.dump(4) << "\n";
    ASSERT_EQ(j["name"], "Cool Robot");
    ASSERT_EQ(j["states"].size(), 5);
};

TEST_F(BetterStateMachineTests, MicrowaveTest) {
    Mode closed_off("closed_off"), closed_on("closed_on"), open("open");
    BetterStateMachine fsm("Microwave");

    fsm.set_initial(closed_off)
    .add_transition("on button pressed", closed_off, closed_on)
    .add_transition("door opened", closed_off, open)
    .add_transition("power level set", closed_off, closed_off)
    .add_transition("off button pressed", closed_on, closed_off)
    .add_transition("door opened", closed_on, open)
    .add_transition("door closed", open, closed_off)
    .add_transition("power level set", open, open);

    json j = fsm.to_json();
    ASSERT_EQ(j["name"], "Microwave");
    ASSERT_EQ(j["states"].size(), 3);
};

TEST_F(BetterStateMachineTests, FSMTest) {
    Mode idle("idle"), busy("busy"), finish("finish");
    BetterStateMachine fsm("FSMTest");

    fsm.set_initial(idle)
    .add_transition("inputs received", idle, busy)
    .add_transition("computation finished", busy, finish)
    .add_transition("output taken", finish, idle);

    json j = fsm.to_json();
    ASSERT_EQ(j["name"], "FSMTest");
    ASSERT_EQ(j["states"].size(), 3);
};

TEST_F(BetterStateMachineTests, ToggleSwitch1Test) {
    Mode off("off"), on("on"), off1("off1"), on1("on1");
    BetterStateMachine fsm("toggle switch 1");

    fsm.set_initial(off)
    .set_propagate(false)
    .add_transition("switch", off, on)
    .add_transition("switch", on, off)
    .add_transition("switch", off1, on1)
    .add_transition("switch", on1, off1);

    json j = fsm.to_json();
    ASSERT_EQ(j["name"], "toggle switch 1");
    ASSERT_EQ(j["states"].size(), 4);
};