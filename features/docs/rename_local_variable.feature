Feature: As a developer I want to rename a local variable within the scope of a method
    @wip
    Scenario: Free function
    Given source code:
    """
    void foo()
    {
    	int y = 3;
    }
    """
    When I run rename local variable from "y" to "z"
    Then there should be 1 changes
    And there should be a replacement of "y" with "z" in line 3