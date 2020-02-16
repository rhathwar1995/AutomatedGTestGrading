//
// Created by Rajendra Hathwar on 2020-01-18.
//

#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <stdlib.h>
#include "gtest/gtest.h"
#include "solutions.h"
#include "rpn.h"
#include "limits.h"
#include <vector>


using std::string;
using std::vector;

#define EPSILON DBL_EPSILON*10.0 // double tolerance
#define DBL_PRECISION 0.00001
#define Q1POINTS 100.0
#define Q2POINTS 100.0
#define Q3POINTS 100.0
#define Q4POINTS 100.0
#define Q5POINTS 100.0
#define Q6POINTS 100.0
#define NUM_QUESTIONS 6 // overestimated number of questions
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

class Question3 : public Question {
protected:
    Question3() {
        id = 2;
        totals[id] = Q3POINTS;
        num_tests[id]++;
    }
};

class Question4 : public Question {
protected:
    Question4() {
        id = 3;
        totals[id] = Q4POINTS;
        num_tests[id]++;
    }
};

class Question5 : public Question {
protected:
    Question5() {
        id = 4;
        totals[id] = Q5POINTS;
        num_tests[id]++;
    }
};

class Question6 : public Question {
protected:
    Question6() {
        id = 5;
        totals[id] = Q5POINTS;
        num_tests[id]++;
    }
};

/*
 * Question 1: running_total *************************************************
 */

class RunningTotalTests : public Question1,
                    public ::testing::WithParamInterface<std::pair<int, int>> {
};

std::vector <std::pair <int, int>> tvForRunningTot =
    { std::make_pair(0, 0)
    , std::make_pair(0, 0)
    , std::make_pair(1, 1)
    , std::make_pair(0, 1)
    , std::make_pair(-1, 0)
    , std::make_pair(0, 0)
    , std::make_pair(-65, -65)
    , std::make_pair(0, -65)
    , std::make_pair(64, -1)
    , std::make_pair(2, 1)
    , std::make_pair(-101, -100)
    };
/*
 * Parameterized test for testing if the running_total method
 * is correctly calculating the sum
 */
TEST_P(RunningTotalTests, RunningTotal) {
    std::pair<int, int> pair = GetParam();

    // Call the student's api
    int result = running_total(std::get<0>(pair));
    int expected = std::get<1>(pair);

    ASSERT_EQ(result, expected);
};

/*
 * parameterizes the RunningTotalTests, TEST_P class above.
 */
INSTANTIATE_TEST_CASE_P(RunningTotalTests,
        RunningTotalTests,
        testing::ValuesIn(tvForRunningTot)
);

/*
 * Question 2 *************************************************
 */

class ReverseInPlaceTests : public Question2,
                    public testing::WithParamInterface<std::pair <std::vector<int>, std::vector<int>>> {
};

std::vector <std::pair <std::vector<int>, std::vector<int>>> tvForRevInPlace =
    { { {1, 2, 3, 4}, {4, 3, 2, 1} }
    , { {0, -1, 3, 0}, {0, 3, -1, 0} }
    , { {0}, {0} }
    , { {-231, 902}, {902, -231} }
    , { {INT_MAX, INT_MIN, 0, INT_MIN, INT_MAX}, {INT_MAX, INT_MIN, 0, INT_MIN, INT_MAX} }
    , { {56, -260, 062}, {062, -260, 56} }
    , { {0, 9, 9, 8, 7, 6}, {6, 7, 8, 9, 9, 0} }
    };


//Param A name the test class, Param B good name for what the tests represent
TEST_P(ReverseInPlaceTests, ReverseInPlace) {
    std::pair <vector<int>, vector<int>> pair = GetParam();

    int len = std::get<0>(pair).size();
    int testArray[len], expectedArray[len];
    std::copy(std::get<0>(pair).begin(), std::get<0>(pair).end(), testArray);
    std::copy(std::get<1>(pair).begin(), std::get<1>(pair).end(), expectedArray);

    // Call the student's api
    reverse_in_place(testArray, len);
    for(int i = 0; i < len; ++i)
    {
        ASSERT_EQ(testArray[i], expectedArray[i]);
    }
};

//Param A random name, Param B test class and Param C list of inputs.
INSTANTIATE_TEST_CASE_P(ReverseInPlaceTests,
        ReverseInPlaceTests,
        testing::ValuesIn(tvForRevInPlace)
);

/*
 * Question 3 *************************************************
 */

class ReverseTests : public Question3,
                    public testing::WithParamInterface<std::pair <std::vector<int>, std::vector<int>>> {
};

//Param A name the test class, Param B good name for what the tests represent
TEST_P(ReverseTests, Reverse) {
    std::pair <vector<int>, vector<int>> pair = GetParam();

    int len = std::get<0>(pair).size();
    int testArray[len], expectedArray[len];
    std::copy(std::get<0>(pair).begin(), std::get<0>(pair).end(), testArray);
    std::copy(std::get<1>(pair).begin(), std::get<1>(pair).end(), expectedArray);

    // Call the student's api
    int *result = reverse(testArray, len);
    for(int i = 0; i < len; ++i)
    {
        ASSERT_EQ(result[i], expectedArray[i]);
    }

    free(result);
};

//Param A random name, Param B test class and Param C list of inputs.
INSTANTIATE_TEST_CASE_P(ReverseTests,
        ReverseTests,
        testing::ValuesIn(tvForRevInPlace)
);

/*
 * Question 4 *************************************************
 */

class NumInstancesTests : public Question4,
                    public testing::WithParamInterface<std::pair <std::vector<int>, int>> {
};

std::vector <std::pair <std::vector<int>, int>> tvForNumInst =
    { { {11, 22, 33, 44}, 3 }
    , { {3, 3, 3, 3}, 3 }
    , { {0, -1, 3, 0, 0, 0}, -1 }
    , { {0}, 0 }
    , { {0}, -9 }
    , { {-231, 902, 789, 123, 111, -111, 0}, 1 }
    , { {-231, 902, 789, 123, 111, -111, 0}, 0 }
    , { {INT_MAX, INT_MIN, 0, INT_MIN, INT_MAX}, INT_MAX }
    };

//Param A name the test class, Param B good name for what the tests represent
TEST_P(NumInstancesTests, NumInstances) {
    std::pair <vector<int>, int> pair = GetParam();
    int len = std::get<0>(pair).size();
    int val = std::get<1>(pair);
    int arr[len];
    std::copy(std::get<0>(pair).begin(), std::get<0>(pair).end(), arr);

    int instances = 0;
    for (int i = 0; i < len; i++){
        if (val == arr[i]){
            instances++;
        }
    }

    int result = num_instances(arr, len, val);
    ASSERT_EQ(result, instances);
};

//Param A random name, Param B test class and Param C list of inputs.
INSTANTIATE_TEST_CASE_P(NumInstancesTests,
        NumInstancesTests,
        testing::ValuesIn(tvForNumInst)
);

/*
 * Question 5 *************************************************
 */

class MapTests : public Question5,
                    public testing::WithParamInterface<std::vector<Point>> {
};

Point negate(Point p) {
    return { -p.x, -p.y, -p.z };
}

std::vector <std::vector<Point>> tvForMap =
    { { { 0, -0, 0}, { 3, -3, 3}, { -2, -1, -3} }
    , { { 0, -9, 0}, { 1, 7, 87}, { -2, 78, -3}, { 57, 879, -3}, { 0, -0, -3} }
    , { { 150, 9, -0}, { 5, 7, -3}, { 7, 79, -9}, { +0, -0, -3} }
    };

//Param A name the test class, Param B good name for what the tests represent
TEST_P(MapTests, Map) {
    std::vector<Point> testVec = GetParam();
    int len = testVec.size();
    Point arr[len], safe_arr[len];
    std::copy(testVec.begin(), testVec.end(), arr);
    std::copy(testVec.begin(), testVec.end(), safe_arr);

    Point * b = map(arr, len, negate);
    for(int i = 0; i < len; ++i) {
        ASSERT_EQ(b[i].x, -safe_arr[i].x);
        ASSERT_EQ(b[i].y, -safe_arr[i].y);
        ASSERT_EQ(b[i].z,- safe_arr[i].z);
    }
    free(b);
    //delete[] b;
};

//Param A random name, Param B test class and Param C list of inputs.
INSTANTIATE_TEST_CASE_P(MapTests,
        MapTests,
        testing::ValuesIn(tvForMap)
);

/*
 * Question 6 *************************************************
 */

class BaseRpnTests : public Question6 {
};

class RpnTests : public Question6,
                    public testing::WithParamInterface<std::vector<double>> {
};

std::vector <std::vector<double>> tvForRpnDiv =
    { {12, -0.5, 24, 36, 56, 9} //9 - top
    , {0.5, 0.05} // 0.05 - top
    , {-89, -96.025, 0, -98.23}
    };

//Param A name the test class, Param B good name for what the tests represent
TEST_P(RpnTests, BasicDivision) {
    std::vector<double> testVec = GetParam();
    int len = testVec.size();

    rpn_init();
    for(int i = 0; i < len; ++i)
        rpn_push(testVec[i]);

    rpn_div();
    EXPECT_NEAR(rpn_pop(), testVec[len-2]/testVec[len-1], DBL_PRECISION);
    EXPECT_EQ(rpn_error(), OK);
    rpn_free();
};

TEST_F(RpnTests, OverflowError) {
    rpn_init();
    rpn_push(DBL_MAX);
    rpn_push(0.9);
    rpn_div();
    EXPECT_EQ(rpn_error(), OVERFLOW_ERROR);
    rpn_free();
};

TEST_F(RpnTests, DivByZeroError) {
    rpn_init();
    rpn_push(0);
    rpn_push(0);
    rpn_div();
    EXPECT_EQ(rpn_error(), DIVIDE_BY_ZERO_ERROR);
    rpn_free();
};

TEST_F(RpnTests, BinaryError) {
    rpn_init();
    rpn_push(1);
    rpn_div();
    EXPECT_EQ(rpn_error(), BINARY_ERROR);  
    rpn_free();
};

TEST_F(BaseRpnTests, Reallocation) {
    rpn_init();
    for (int i = 0; i < 350; i++)
        rpn_push(i);
    for (int i = 349; i >= 0; i--)
        EXPECT_NEAR(rpn_pop(), i, DBL_PRECISION);
    rpn_free();
};

//Param A random name, Param B test class and Param C list of inputs.
INSTANTIATE_TEST_CASE_P(RpnTests,
        RpnTests,
        testing::ValuesIn(tvForRpnDiv)
);