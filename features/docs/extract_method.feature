Feature: As a developer I want to extract code into methods to make my code more readable
    @done
    Scenario: Free function without arguments
        Given source code:
        """
        #include <iostream>
        void someFunc()
        {
            std::cout << "counting" << std::endl;
            for (int i = 0; i < 10; ++i)
                std::cout << " " << i;
            std::cout << std::endl;
        }
        """
        When I run function extraction from "for (" to "<< i;" with name "runLoop"
        Then there should be 2 changes
        And there should be an insertion:
        """
        void runLoop()
        {
            for (int i = 0; i < 10; ++i)
                std::cout << " " << i;
        }

        """
        And there should be a replacement from "for (" to "<< i;" with "runLoop();"
    @done
    Scenario: Partial selection should work as full selection
        Given source code:
        """
        void f(int);
        
        void func()
        {
            for (int i = 0; i < 5; ++i)
            {
                f(i);
            }
            f(10);
            f(20);
        }
        """
        When I run function extraction from "i);" to "f(2" with name "partial"
        Then there should be 2 changes
        And there should be a replacement from "for (" to "20);" with "partial();"
        And there should be an insertion:
        """
        void partial()
        {
            for (int i = 0; i < 5; ++i)
            {
                f(i);
            }
            f(10);
            f(20);
        }

        """
    @done
    Scenario: Extracted function should be inserted before original function
        Given source code:
        """
        #include <iostream>
        void f(int);
        void complex()
        {
            f(1);
            std::cout << 2;
            f(2);
        }
        void other();
        """
        When I run function extraction for "cout << 2" with name "print"
        Then there should be an insertion before "void complex":
        """
        void print()
        {
            std::cout << 2;
        }

        """
    @done
    Scenario: Referenced local variables should be passed to the extracted function
        Given source code:
        """
        void other1(int);
        void other2();
        void other3(int, float);
        void original()
        {
            int i = 7;
            float f = 9.5f;
            other1(i);
            other2();
            other3(i + 5, f * 2);
        }
        """
        When I run function extraction from "other1(i)" to "other3(i + 5" with name "with_args"
        Then there should be an insertion:
        """
        void with_args(int i, float f)
        {
            other1(i);
            other2();
            other3(i + 5, f * 2);
        }

        """
        And there should be a replacement with "with_args(i, f);"
    @done
    Scenario: Extraction of local variables declared in and used after the selected block should prevent the extraction
        Given source code:
        """
        void other3(int, int);
        void original()
        {
            int i = 7, j = 9;
            i += 2;
            j += 5;
            other3(i, j);
        }
        """
        When I run function extraction from "int i = 7" to "j += 5" with name "bad"
        Then it should fail with a message "Cannot extract 'bad'. Following variables are in use after the selected statements: i, j"
    @done
    Scenario: Local variables used after but not declared in the selected block should not prevent the extraction
        Given source code:
        """
        void other(int);
        void original()
        {
            int j = 9;
            j += 5;
            int i = 7;
            i += 2;
            other(i);
        }
        """
        When I run function extraction from "int j = 9" to "j += 5" with name "good"
        Then there should be a replacement with "good();"
    @done
    Scenario: Method extraction should not add empty line at the end of method body when extracting a variable declaration. Newline should be added after extracted method call.
        Given source code:
        """
        void simpleFunction()
        {
            int a = 666;
            int b = 7;
            int c = 123;
        }
        """
        When I run function extraction for "int b = 7;" with name "extracted"
        Then there should be an insertion:
        """
        void extracted()
        {
            int b = 7;
        }

        """
        And there should be a replacement for "int b = 7;" with "extracted();"
    @wip
    Scenario: Extraction of statement in try block is supported
        Given source code:
        """
        void myFunction()
        {
            try
            {
                int a = 2;
                int b = a;
            }
            catch (...)
            {}
        }
        """
        When I run function extraction for "int b = a;" with name "extracted"
        Then there should be an insertion:
        """
        void extracted(int a)
        {
            int b = a;
        }
        """
        And there should be a replacement for "int b = a;" with "extracted(a);"
    @done
    Scenario: should extract if statements
        Given source code:
        """
        void g(int);
        void f()
        {
            if (true)
                g(7);
        }
        """
        When I run function extraction from "if (" to "g(7);" with name "extracted"
        Then there should be an insertion:
        """
        void extracted()
        {
            if (true)
                g(7);
        }

        """
        And there should be a replacement with "extracted();"

    @done
    Scenario: should extract if statements with else clauses
        Given source code:
        """
        void g(int);
        void f()
        {
            if (true)
                g(7);
            else g(8);
        }
        """
        When I run function extraction from "if (" to "g(8);" with name "extracted"
        Then there should be an insertion:
        """
        void extracted()
        {
            if (true)
                g(7);
            else g(8);
        }

        """
        And there should be a replacement with "extracted();"
    @done
    Scenario: should extract for statements with variable declaration
        Given source code:
        """
        #include <string>
        void g(int);
        void f()
        {
            for (std::string aux = "";  aux != ";"; aux=";") int x = 3;
        }
        """
        When I run function extraction from "for (" to "3;" with name "extracted"
        Then there should be an insertion:
        """
        void extracted()
        {
            for (std::string aux = "";  aux != ";"; aux=";") int x = 3;
        }

        """
        And there should be a replacement with "extracted();"
    @done
    Scenario: should extract for statements with compound body
        Given source code:
        """
        #include <string>
        void g(int);
        void f()
        {
            for (std::string aux = "";  aux != ";"; aux=";") {
                g(7); }
        }
        """
        When I run function extraction from "for (" to "g(7); }" with name "extracted"
        Then there should be an insertion:
        """
        void extracted()
        {
            for (std::string aux = "";  aux != ";"; aux=";") {
                g(7); }
        }

        """
        And there should be a replacement with "extracted();"
    @done
    Scenario: should extract for statements with nested for loops
        Given source code:
        """
        #include <string>
        void g(int);
        void f()
        {
            for (std::string aux = "";  aux != ";"; aux=";")
                for (std::string aux = "";  aux != ";"; aux=";")
                    for (std::string aux = "";  aux != ";"; aux=";"/**/);
        }
        """
        When I run function extraction from "for (" to "/**/);" with name "extracted"
        Then there should be an insertion:
        """
        void extracted()
        {
            for (std::string aux = "";  aux != ";"; aux=";")
                for (std::string aux = "";  aux != ";"; aux=";")
                    for (std::string aux = "";  aux != ";"; aux=";"/**/);
        }

        """
        And there should be a replacement with "extracted();"

