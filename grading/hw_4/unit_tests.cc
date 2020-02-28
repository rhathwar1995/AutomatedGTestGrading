//
// Created by Rajendra Hathwar on 2020-01-18.
//

#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <stdlib.h>
#include "gtest/gtest.h"
#include "complex.h"
#include "typed_array.h"
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
 * Question 1: push, pop, push_front, and pop_front *************************************************
 */

class TypedArrayBasicTests : public Question1,
                    public ::testing::WithParamInterface<int> {
};

//Param A name the test class, Param B good name for what the tests represent
TEST_P(TypedArrayBasicTests, Push) {
    int size = GetParam();
    double  min = -1000,
            max = 1000.0;

    std::vector<double> testVector = dbl_vector(size, min, max);
    TypedArray<double> vec;
    for(auto i : testVector) {
        vec.push(i);
    }

    ASSERT_EQ(vec.size(), size);
    for(int i = 0; i < size; i++) {
        ASSERT_NEAR(vec.get(i), testVector[i], DBL_PRECISION);
    }
};

TEST_P(TypedArrayBasicTests, Pop) {
    int size = GetParam();
    double  min = -1000,
            max = 1000.0;

    std::vector<double> testVector = dbl_vector(size, min, max);
    TypedArray<double> vec;
    for(auto i : testVector)
        vec.push(i);
    for(int i = 0; i < size; i++) {
        vec.pop();
        for (int j = 0; j < size-1-i; j++) {
            ASSERT_NEAR(vec.get(j), testVector[j], DBL_PRECISION);
        }
    }
    try {
        vec.pop();
    } catch (std::range_error e ) {
        ASSERT_STREQ(e.what(), "Cannot pop from an empty array");
    }
};

TEST_P(TypedArrayBasicTests, PushFront) {
    int size = GetParam();
    double  min = -1000,
            max = 1000.0;

    std::vector<double> testVector = dbl_vector(size, min, max);
    TypedArray<double> vec;
    for(auto i : testVector)
        vec.push_front(i);

    ASSERT_EQ(vec.size(), size);
    for(int i = 0; i < size; i++) {
        ASSERT_NEAR(vec.get(i), testVector[size-1-i], DBL_PRECISION);
    }
};

TEST_P(TypedArrayBasicTests, PopFront) {
    int size = GetParam();
    double  min = -1000,
            max = 1000.0;

    std::vector<double> testVector = dbl_vector(size, min, max);
    TypedArray<double> vec;
    for(auto i : testVector)
        vec.push(i);

    for(int i=0; i < size; i++) {
        vec.pop_front();
        for(int j = i+1; j < size; j++) {
            ASSERT_NEAR(vec.get(j-i-1), testVector[j], DBL_PRECISION);
        }
    }
    try {
        vec.pop_front();
    } catch (std::range_error e ) {
        ASSERT_STREQ(e.what(), "Cannot pop from an empty array");
    }
};

/*
 * parameterizes the TypedArrayBasicTests, TEST_P class above.
 */
INSTANTIATE_TEST_CASE_P(TypedArrayBasicTests,
        TypedArrayBasicTests,
        testing::Range(0, 900, 300)
);

/*
 * Question 2 *************************************************
 */

class TypedArrayConcatTests : public Question2,
                    public testing::WithParamInterface<std::vector<double>> {
};

std::vector <std::vector<double>> concatTestVev =
    { {1.235, 2.023, 3.56, 4}
    , {0.369, -1.36, 3, 0}
    , {0.9635, 3.63, -1, 0}
    , {0}
    , {-231, 902.6395, -0.2902, -5.36231}
    , {INT_MAX, INT_MIN, 0, INT_MIN, INT_MAX, INT_MAX, INT_MIN, 0, INT_MIN, INT_MAX}
    , {56, -260, 062, 062, -260, 56}
    , {0, 9, 9, 8, 7, 6, 6, 7, 8, 9, 9, 0}
    , {INFINITY, -INFINITY}
    };


//Param A name the test class, Param B good name for what the tests represent
TEST_P(TypedArrayConcatTests, Concat) {
    std::vector<double> testVec = GetParam();
    int size = testVec.size();
    TypedArray<double> a;
    for(int i = 0; i < size; i++) {
        a.set(i, testVec[i]);
    }

    TypedArray<double> b = a.concat(a).concat(a).concat(a);

    ASSERT_EQ(a.size(), size);
    for(int i = 0; i < size; i++) {
        ASSERT_EQ(a.get(i), testVec[i]);
    }

    ASSERT_EQ(b.size(), size * 4);
    for(int i = 0; i < size * 4; i++) {
        ASSERT_EQ(b.get(i), testVec[i % size]);
    }
};

//Param A random name, Param B test class and Param C list of inputs.
INSTANTIATE_TEST_CASE_P(TypedArrayConcatTests,
        TypedArrayConcatTests,
        testing::ValuesIn(concatTestVev)
);

/*
 * Question 3 *************************************************
 */

class TypedArrayReverseTests : public Question3,
                    public testing::WithParamInterface<std::vector<char>> {
};

std::vector <std::vector<char>> reverseTestVec =
    { {'a','b','c','d','e','f','g','h'}
    , {'i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'}
    , {'r'}
    , {'1','2','3','A','B'}
    , {'C','D','E'}
    , {'F','G'}
    , {'K','G','F','B','A','C','K'}
    , {'#'}
    };

//Param A name the test class, Param B good name for what the tests represent
TEST_P(TypedArrayReverseTests, Reverse) {
    std::vector<char> testVec = GetParam();
    int size = testVec.size();
    TypedArray<char> a;
    for(int i = 0; i < size; i++) {
        a.set(i, testVec[i]);
    }

    TypedArray<char> &b = a.reverse();
    ASSERT_EQ(&a, &b); // Check references are the same
    
    for(int i = 0; i < size; i++) {
        ASSERT_EQ(a.get(i), testVec[size-1-i]);
    }
};

//Param A random name, Param B test class and Param C list of inputs.
INSTANTIATE_TEST_CASE_P(TypedArrayReverseTests,
        TypedArrayReverseTests,
        testing::ValuesIn(reverseTestVec)
);

/*
 * Question 4 *************************************************
 */

class TypedArrayOperatorTests : public Question4,
                    public testing::WithParamInterface<std::vector<std::string>> {
};

std::vector <std::vector<std::string>> concatOperTestVec =
    { {"This", "is", "not", "a", "drill"}
    , {"Tea", "Table"}
    , {"Mango", "Apple", "Orange"}
    , {"16WP", "OB86", "apzX", "X7CU", "q86D", "KOwJ", "U7RF", "4l54", "0WXf9p0j"}
    , {"yduW5WlcBJ75", "fS3zto", "mlAbpK9ac6T8", "W4Wk2E0", "sRs", "F", "vnR5", "H6OD2", "ozfDFzA0wlQ1"}
    , {"789456"}
    , {"987", "654", "321", "098"}
    , {"16WPOB86apzXX7CUq86D", "KOwasddasd8u89ujuufJ", "Usadsadsad879787RF", "45465asd4a65d46al54", "0WXf9p0j"}
    };

//Param A name the test class, Param B good name for what the tests represent
TEST_P(TypedArrayOperatorTests, ConcatOperator) {
    std::vector<std::string> testVec = GetParam();
    int size = testVec.size();
    TypedArray<std::string> a;
    for(int i = 0; i < size; i++) {
        a.set(i, testVec[i]);
    }

    TypedArray<std::string> b = a + a + a + a;

    ASSERT_EQ(a.size(), size);
    for(int i = 0; i < size; i++) {
        ASSERT_EQ(a.get(i), testVec[i]);
    }

    ASSERT_EQ(b.size(), size * 4);
    for(int i = 0; i < size * 4; i++) {
        ASSERT_EQ(b.get(i), testVec[i % size]);
    }
};

//Param A random name, Param B test class and Param C list of inputs.
INSTANTIATE_TEST_CASE_P(TypedArrayOperatorTests,
        TypedArrayOperatorTests,
        testing::ValuesIn(concatOperTestVec)
);

/*
 * Question 5 *************************************************
 */

class ComplexTests : public Question5,
                    public testing::WithParamInterface<std::pair<double, double>> {
};

std::vector <std::pair<double, double>> complexTestVec =
    { {0.0, -0}
    , {5.36, -7.235}
    , {-150.23, 9.0023}
    , {-79.326, -90.223}
    , {0, 89}
    };

//Param A name the test class, Param B good name for what the tests represent
TEST_P(ComplexTests, Real_Imag) {
    std::pair<double, double> pair = GetParam();
    double r = std::get<0>(pair),
           i = std::get<1>(pair);
    Complex a = Complex (r, i);
    ASSERT_EQ(a.re(), r);
    ASSERT_EQ(a.im(), i);
};

TEST_P(ComplexTests, Conjugate) {
    std::pair<double, double> pair = GetParam();
    double r = std::get<0>(pair),
           i = std::get<1>(pair);
    Complex a = Complex(r, i);
    Complex conj = a.conjugate();
    ASSERT_EQ(conj.re(), r);
    ASSERT_EQ(conj.im(), -i);
};

//Param A random name, Param B test class and Param C list of inputs.
INSTANTIATE_TEST_CASE_P(ComplexTests,
        ComplexTests,
        testing::ValuesIn(complexTestVec)
);

class ComplexOperatorTests : public Question5,
                    public testing::WithParamInterface<std::tuple<double, double, double, double, bool>> {
};

std::vector <std::tuple<double, double, double, double, bool>> complexOpTestVec =
    { {0.0, -0, 0, 0, true}
    , {5.36, -7.235, 56.36, 85.69, false}
    , {-150.23, -9.0023, -150.23, -9.0023, true}
    , {-79.326, -90.223, -90.223, -79.326, false}
    , {0, 89, 89, 0, false}
    , {8.9999, -9.23, 8.9999, -9.23, true}
    };

TEST_P(ComplexOperatorTests, Multiply) {
    std::tuple<double, double, double, double, bool> testTuple = GetParam();
    double r1 = std::get<0>(testTuple),
           i1 = std::get<1>(testTuple),
           r2 = std::get<2>(testTuple),
           i2 = std::get<3>(testTuple);
    Complex a = Complex(r1, i1);
    Complex b = Complex(r2, i2);
    Complex mult = a * b;
    ASSERT_NEAR(mult.re(), r1*r2 - i1*i2, DBL_PRECISION);
    ASSERT_NEAR(mult.im(), r1*i2 + i1*r2, DBL_PRECISION);
};

TEST_P(ComplexOperatorTests, Add) {
    std::tuple<double, double, double, double, bool> testTuple = GetParam();
    double r1 = std::get<0>(testTuple),
           i1 = std::get<1>(testTuple),
           r2 = std::get<2>(testTuple),
           i2 = std::get<3>(testTuple);
    Complex a = Complex(r1, i1);
    Complex b = Complex(r2, i2);
    Complex add = a + b;
    ASSERT_NEAR(add.re(), r1+r2, DBL_PRECISION);
    ASSERT_NEAR(add.im(), i1+i2, DBL_PRECISION);
};

TEST_P(ComplexOperatorTests, Equal) {
    std::tuple<double, double, double, double, bool> testTuple = GetParam();
    double r1 = std::get<0>(testTuple),
           i1 = std::get<1>(testTuple),
           r2 = std::get<2>(testTuple),
           i2 = std::get<3>(testTuple);
    bool equal = std::get<4>(testTuple);
    Complex a = Complex(r1, i1);
    Complex b = Complex(r2, i2);
    ASSERT_EQ(a == b, equal);
};

//Param A random name, Param B test class and Param C list of inputs.
INSTANTIATE_TEST_CASE_P(ComplexOperatorTests,
        ComplexOperatorTests,
        testing::ValuesIn(complexOpTestVec)
);
