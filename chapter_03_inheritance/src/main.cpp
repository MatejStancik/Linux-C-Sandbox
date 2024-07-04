/*====# INHERITANCE #====*/
/*

Inheritance is one of the most common traits of polymorphism.
By inheriting code, the child classes also gain all the other values of the
parent class, vso we don't have to rewrite the class fully.

Any class can become a child class by extending the parent class.
An entire class can be extended, or just the members with specific access modifiers.

*/
/*====# POLYMORPHISM #====*/
/*

Polymorphism is one of the most important concepts in OOP.
In OOP, polymorphism is the provision of a single interface to entities
of different types.

Fun fact: The concept is borrowed from a principle in biology
where an organism or species can have many different forms or stages.

The most commonly recognized major forms of polymorphism are:

## Ad hoc polymorphism ##
Defines a common interface for an arbitrary set of individually specified types.

## Parametric polymorphism ##
Not specifying concrete types and instead use
abstract symbols that can substitute for any type.

## Subtyping ##
When a name denotes instances of many different classes related by
some common superclass.

*/
/*====# VIRTUAL #====*/
/*

A virtual function is a member function that is declared within a base class and
is re-defined (overridden) by a derived class.
When you refer to a derived class object using a pointer or a reference to the base
class, you can call a virtual function for that object and execute the
derived class’s version of the method instead.

Virtual functions ensure that the correct function is called for an object,
egardless of the type of reference (or pointer) used for the function call.

* They are mainly used to achieve Runtime polymorphism.
* Functions are declared with a virtual keyword in a base class.
* The resolving of a function call is done at runtime.

//==# A VTABLE #==//

The vTable, or Virtual Table, is a table of function pointers that is created
by the compiler to support dynamic polymorphism. Whenever a class contains a
virtual function, the compiler creates a Vtable for that class.
Each object of the class is then provided with a hidden pointer to this table,
known as Vptr.

The Vtable has one entry for each virtual function accessible by the class.
These entries are pointers to the most derived function that the current object should call.

*/

/*==# INCLUDES #==*/
#include <iostream>

/*==# DEFINES #==*/

#define TESTCLASS_DEFAULT 0
#define TESTCLASS_DYNAMICVALUE_ADDITION 3
#define safe_free(pointer) \
    if (pointer) {         \
        free (pointer);    \
    }

/*==# GLOBAL FUNCTIONS #==*/

/*==# CLASSES #==*/

// 1. INTERFACE //
/*

C++ by itself has no real concept of interfaces so
we can only achieve that using a purely abstract class.

ConcreteClass implements the abstract class AbstractInterface
and creates the fucntions.

*/

class AbstractInterface {

    public:
    virtual char returnChar ()  = 0;
    virtual int returnNumber () = 0;
};

class ConcreteClass : AbstractInterface {

    public:
    char returnChar () {
        return 'e';
    }

    int returnNumber () {
        return 15;
    }
};

// 2. VIRTUAL DESTRUCTOR //
/*

A virtual destructor is a very helpful method of properly destroying the object.
Making the base class destructor virtual guarantees that the object of derived class
is destructed properly (both base class and derived class destructors are called)

*/

class VirtualDestructorClass {
    public:
    virtual ~VirtualDestructorClass () {
        std::cout << "VirtualDestructorClass destructor! I am the big boy." << std::endl;
    }
};

class SubClass_VirtualDestructor : VirtualDestructorClass {
    public:
    ~SubClass_VirtualDestructor () {
        std::cout
        << "SubClass_VirtualDestructor destructor! I wish I was the big boy."
        << std::endl;
    }
};

// 3. POLYMORPHISM AND OVERRIDING //
/*

Very simply put, overriding is just a form of polymorphism. All overriding really does is
well... override an existing function from the parent class and replace it.

The override keyword does just that, but allows us to override virtual functions.
It also serves as a simple check if you are... in fact... overriding something.

Pretty cool, right?

*/

class PolymorphicClass {
    public:
    virtual bool isFiveStar () {
        return true;
    }
    void sayLine () {
        std::cout << "I am the peak of function evolution." << std::endl;
    }
};

class OverridingClass : PolymorphicClass {
    public:
    virtual bool isFiveStar () override {
        return false;
    }

    void sayLine () {
        std::cout << "I'm not just like the rest of you. I'm stronger. I'm "
                     "smarter. I'm better. I AM BETTER."
                  << std::endl;
    }
};

// 4. DIAMOND INHERITANCE PROBLEM (a.k.a why I love C more) //
/*

OOP and inheritance can be helpful, sure. But then comes the scary topic of one class
inheriting from multiple classes, which inherit from one base class (diamond shape yeah)


*/

class A {
    public:
    void whoisthatClass () {
        std::cout << "It's A!" << std::endl;
    }
};

class B : virtual public A {
    public:
    void whoisthatClass () {
        std::cout << "It's B!" << std::endl;
    }
};

class C : virtual public A {
    public:
    void whoisthatClass () {
        std::cout << "It's C!" << std::endl;
    }
};

// WHAT FUNCTION WILL IT BE? B OR C?
/*

Your interface or compiler will quickly warn you that it's impossible to tell.
My VScode warned me with "Member 'whoisthatClass' found in multiple base classes
of different typesclang(ambiguous_member_multiple_subobject_types)"

There are two ways to fix this.

1. Calling a function from the specific derived class ( B::whoisthatClass())
2. Virtual inheritance    class B : virtual A

In this chapter, I used the first one for the sake of convenience.

*/

class D : public B, public C {};

// 5. OBJECT SLICING //
/*

No, we are not calling the enemy fed Yasuo to destroy our object.
Object slicing is an unfortunate side effect of upcasting a child class
to the parent class. This destroys the values of the child class (SLICES them off)

*/

// NOTE: Parent Slicer sounds like a cool horror movie name.

class ParentSlicerClass {
    public:
    int a = 4;
    int b = 10;
};

class ClassToBeSliced : public ParentSlicerClass {
    public:
    int a = 8;
    int b = 20;
    int c = 15;
    int d = 21;
};

int main () {

    /*==# SCENARIO 1 #==*/
    // Testing the Interface inheritance

    ConcreteClass InterfaceTest;

    std::cout << std::endl << "## SCENARIO 1 ##" << std::endl;
    std::cout << "ConcreteClass.returnChar = " << InterfaceTest.returnChar ()
              << " (expecting 'e')" << std::endl;
    std::cout << "ConcreteClass.returnNumber = " << InterfaceTest.returnNumber ()
              << " (expecting '15')" << std::endl;

    /*==# SCENARIO 2 #==*/
    // Testing virtual destructor

    VirtualDestructorClass* virtualdestructor = new VirtualDestructorClass ();
    SubClass_VirtualDestructor* sub_virtualdestructor = new SubClass_VirtualDestructor ();

    std::cout << std::endl << "## SCENARIO 2 ##" << std::endl;
    std::cout
    << "1. Destroying VirtualDestructorClass. Expecting only destructor." << std::endl
    << std::endl;
    delete virtualdestructor;
    std::cout << std::endl;
    std::cout << "2. Destroying SubClass_VirtualDestructor. Expecting this "
                 "destructor and parent destructor."
              << std::endl
              << std::endl;
    delete sub_virtualdestructor;

    /*==# SCENARIO 3 #==*/
    // Polymorphism

    PolymorphicClass polymorphism;
    OverridingClass override;

    std::cout << std::endl << "## SCENARIO 3 ##" << std::endl;
    std::cout << "PolymorphicClass.isFiveStar = " << polymorphism.isFiveStar ()
              << " (expecting 1)" << std::endl;
    std::cout << "PolymorphicClass.sayLine = ";
    polymorphism.sayLine ();
    std::cout << " (expecting gloating)" << std::endl;

    std::cout << "OverridingClass.isFiveStar = " << override.isFiveStar ()
              << " (expecting 0)" << std::endl;
    std::cout << "OverridingClass.sayLine = ";
    override.sayLine ();
    std::cout << " (expecting Homelander's breakdown)" << std::endl;

    /*==# SCENARIO 4 #==*/
    // Diamond inheritance problem

    D inheritance;

    std::cout << std::endl << "## SCENARIO 4 ##" << std::endl;
    std::cout << "1. Calling B.whoisthisClass (inherited)" << std::endl;
    inheritance.B::whoisthatClass ();
    std::cout << "2. Calling C.whoisthisClass (inherited)" << std::endl;
    inheritance.C::whoisthatClass ();

    /*==# SCENARIO 5 #==*/
    // Object slicing
    std::cout << std::endl << "## SCENARIO 5 ##" << std::endl;

    ClassToBeSliced sliced;
    ParentSlicerClass slicer = sliced;

    std::cout << "ParentSlicerClass.a = " << slicer.a << " (expecting 4)" << std::endl;
    std::cout << "ParentSlicerClass.b = " << slicer.b << " (expecting 10)" << std::endl;

    // UNCOMMENT TO TEST
    // std::cout << "ParentSlicerClass.c = " << slicer.c;
    // std::cout << "ParentSlicerClass.c = " << slicer.d;

    /*==# THE END #==*/
    return 0;
}
