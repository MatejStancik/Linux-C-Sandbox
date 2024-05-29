/*====# THE RULE OF FIVE IN C++ #====*/
/*
The Rule of Five is an efficient way to correctly handle data semantics.
It states that:

"If one of these functions is defined for a class, it's better to define all of them:

* Destructor
* Copy Constructor
* Copy Assignment Operator
* Move Constructor
* Move Assignment Operator
"

By following this rule, you effectively elimitale lots of potential data leaks and 
correctly handle dynamic allocation, should you use it in your class.
If we just copy all the members, we create something called a "shallow copy".
A shallow copy takes all the pointers of the previous class, but does not make it's own data.
So if you were to destroy the original object you copied from, the new "copy"'s pointers would point
to non-existent data, causing a segmentation fault and a feeling of Impostor Syndrome.

*/

/*==# INCLUDES #==*/
#include <iostream>
#include <string>
#include <utility>

/*==# DEFINES #==*/

#define TESTCLASS_DEFAULT 0
#define TESTCLASS_DYNAMICVALUE_ADDITION 3
#define safe_free(pointer) if (pointer){free(pointer);}

/*==# CLASSES #==*/

class TestClass {

    private:
        int value;
        int *dynamic_value = NULL;

        void log(std::string extra_text) {
            std::cout << "TestClass instance '" << this << "' " << extra_text << "\n";
            std::cout << "value = " << value << " dynamic_value = ";
            dynamic_value ? std::cout << *dynamic_value : std::cout << "FREE (NULL)";
            std::cout << "\n";
        }

    public:
        /*==# DEFAULT CONSTRUCTOR #==*/
        /* This function is called at the creation of a new instance of the class */
        /* The function shares the name with the class.*/
        TestClass(int new_value = TESTCLASS_DEFAULT) {
            value = new_value;
            dynamic_value = (int*)malloc(sizeof(int));
            *dynamic_value = new_value + TESTCLASS_DYNAMICVALUE_ADDITION;
            std::cout << "TestClass instance '" << this << "' created using the default Constructor!" << std::endl;
            std::cout << "value = " << value << " dynamic_value = " << *dynamic_value << std::endl << std::endl;
        };

        /*==# DEFAULT DESTRUCTOR #==*/
        /* This function is called at the destruction of the instance. */
        /* Here, you should free all allocated memory. */
        /* You will be missed, dear TestClass... */
        ~TestClass() {
            log("is being destroyed by the Destructor!");
            if (dynamic_value) {
                free(dynamic_value);
            }
            std::cout << std::endl << "Destruction complete!" << std::endl << std::endl;
        };

        /*==# COPY CONSTRUCTOR #==*/
        /* Note the argument being an instance of TestClass. */
        /* Currently, we make a deep copy by allocating our memory and setting the value afterwards. */
        TestClass(const TestClass &source) {
            value = source.value;
            safe_free(dynamic_value);
            dynamic_value = (int*)malloc(sizeof(int));
            *dynamic_value = source.value + TESTCLASS_DYNAMICVALUE_ADDITION;
            log("created using a Copy Constructor!");
        };

        /*==# COPY ASSIGMENT OPERATOR #==*/
        /* This function is called when we assign an instance to already existing instance. */
        /* So if we have an instance called A and B and we try to set B = A after their initalization, */
        /* this function is called. We also check if the instance is not the same, to avoid a worthless operation. */
        TestClass &operator=(const TestClass &source) {
            if (this != &source) {
                value = source.value;
                safe_free(dynamic_value);
                dynamic_value = (int*)malloc(sizeof(int));
                *dynamic_value = source.value + TESTCLASS_DYNAMICVALUE_ADDITION;
            }
            log("updated using a Copy Assigment Operator!");
            return *this;
        };

        /*==# MOVE CONSTRUCTOR #==*/
        /* This function is called when data is moved to this instance. */
        /* The big difference between a copy and a move is, that the allocated data remains */
        /* in the same address, but now it belongs to the new class. */
        TestClass(TestClass&& source) noexcept {
            value = source.value;
            safe_free(dynamic_value);
            dynamic_value = source.dynamic_value;
            source.value = TESTCLASS_DEFAULT;
            source.dynamic_value = nullptr;
            log("created using a Move Constructor!");
        };

        /*==# MOVE ASSIGNMENT OPERATOR #==*/
        /* Same as the copy one above, but with move. */
        /* We set the original to an initialized state. */
        TestClass &operator=(TestClass&& source) noexcept {
            if (this != &source){
                value = source.value;
                safe_free(dynamic_value);   
                dynamic_value = source.dynamic_value;
                source.value = TESTCLASS_DEFAULT;
                source.dynamic_value = nullptr;
            }
            log("updated using a Move Assigmnent Operator!");
            return *this;
        }
};

int main()
{
    /*==# SCENARIO 1 #==*/
    /* Using a default Constructor with the number 15 */
    TestClass instance_A(15);
    
    /*==# SCENARIO 2 #==*/
    /* Using a Copy Constructor to copy from A to B */
    TestClass instance_B = instance_A;
    
    /*==# SCENARIO 3 #==*/
    /* Using a Copy Assignment Operator to copy A to C, despite C being already created. */
    TestClass instance_C;
    instance_C = instance_A;

    /*==# SCENARIO 4 #==*/
    /* Using a Move Constructor to move everything from A to D. */
    /* This will also test, if the copy is correct, otherwise a segfault will happen during Deconstructors. */
    TestClass instance_D = std::move(instance_A);

    /*==# SCENARIO 5 #==*/
    /* Using a Move Assign Operator to move everything from B to E, despite E being already created. */
    TestClass instance_E;
    instance_E = std::move(instance_B);

    return 0;
}
