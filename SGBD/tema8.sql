-- 1. In this exercise, create a program to add a new job into the JOBS table.
-- a. Create a stored procedure called NEW_JOB to enter a new order into the JOBS table.
-- The procedure should accept three parameters. The first and second parameters supply
-- a job ID and a job title. The third parameter supplies the minimum salary. Use the
-- maximum salary for the new job as twice the minimum salary supplied for the job ID.
-- b. Invoke the procedure to add a new job with job ID 'SY_ANAL', job title 'System
-- Analyst', and minimum salary of 6000.
-- c. Check whether a row was added and note the new job ID for use in the next exercise.
-- Commit the changes.

SELECT
  *
FROM
  FUNCTII;

CREATE OR REPLACE PROCEDURE NEW_JOB(
  P_JOB_ID IN FUNCTII.ID_FUNCTIE%TYPE,
  P_JOB_TITLE IN FUNCTII.DENUMIRE_FUNCTIE%TYPE,
  P_MINIMUM_SALARY IN FUNCTII.SALARIU_MIN%TYPE
) AS
BEGIN
  INSERT INTO FUNCTII VALUES (
    P_JOB_ID,
    P_JOB_TITLE,
    P_MINIMUM_SALARY,
    2*P_MINIMUM_SALARY
  );
END NEW_JOB;
/

DELETE FROM FUNCTII
WHERE
  ID_FUNCTIE = 'SY_ANAL';

ROLLBACK;

BEGIN
  NEW_JOB('SY_ANAL', 'System Analyst', 6000);
  IF SQL%ROWCOUNT = 1 THEN
    DBMS_OUTPUT.PUT_LINE('A FOST INTRODUS');
    COMMIT;
  END IF;
EXCEPTION
  WHEN OTHERS THEN
    DBMS_OUTPUT.PUT_LINE('NU A FOST INTRODUS');
END;
 -- 2. In this exercise, create a program to add a new row to the JOB_HISTORY table, for an existing
 -- employee.
 -- a. Create a stored procedure called ADD_JOB_HIST to add a new row into the
 -- JOB_HISTORY table for an employee who is changing his job to the new job ID
 -- ('SY_ANAL') that you created in exercise 1 b.
 -- I The procedure should provide two parameters, one for the employee ID who is changing the job, and the second for the new job ID.
 -- II Read the employee ID from the EMPLOYEES table and insert it into the JOB_HISTORY table. Make the hire date of
 -- this employee as start date and today’s date as end date for this row in the JOB_HISTORY table.
 -- III Change the hire date of this employee in the EMPLOYEES table to today’s date. Update
 -- the job ID of this employee to the job ID passed as parameter (use the 'SY_ANAL' job
 -- ID) and salary equal to the minimum salary for that job ID + 500.
 -- Note: Include exception handling to handle an attempt to insert a nonexistent employee.
 -- b. Execute the procedure with employee ID 106 and job ID 'SY_ANAL' as parameters.
 -- c. Query the JOB_HISTORY and EMPLOYEES tables to view your changes for employee
 -- 106, and then commit the changes.
 CREATE OR REPLACE PROCEDURE ADD_JOB_HIST(P_EMP_ID IN ANGAJATI.ID_ANGAJAT%TYPE, P_JOB_ID IN FUNCTII.ID_FUNCTIE%TYPE) AS EMP ANGAJATI%ROWTYPE;
V_CHECK NUMBER := 0;
NO_EMP_FOUND
EXCEPTION;
    NO_JOB_FOUND EXCEPTION;
    BEGIN
    SELECT
      COUNT(*) INTO V_CHECK
    FROM
      ANGAJATI
    WHERE
      ID_ANGAJAT = P_EMP_ID;
    IF V_CHECK = 0 THEN
      RAISE NO_EMP_FOUND;
    END IF;
    SELECT
      * INTO EMP
    FROM
      ANGAJATI
    WHERE
      ID_ANGAJAT = P_EMP_ID;
    INSERT INTO ISTORIC_FUNCTII VALUES (
      EMP.ID_ANGAJAT,
      EMP.DATA_ANGAJARE,
      SYSDATE,
      EMP.ID_FUNCTIE,
      EMP.ID_DEPARTAMENT
    );
    SELECT
      COUNT(*) INTO V_CHECK
    FROM
      FUNCTII
    WHERE
      ID_FUNCTIE = P_JOB_ID;
    IF V_CHECK = 0 THEN
      RAISE NO_JOB_FOUND;
    END IF;
    UPDATE ANGAJATI SET DATA_ANGAJARE = SYSDATE, ID_FUNCTIE = P_JOB_ID, SALARIUL = (
      SELECT
        SALARIU_MIN
      FROM
        FUNCTII
      WHERE
        ID_FUNCTIE = P_JOB_ID
    ) + 500 WHERE ID_ANGAJAT = EMP.ID_ANGAJAT;
    EXCEPTION
  WHEN NO_EMP_FOUND THEN
    DBMS_OUTPUT.PUT_LINE('Angajatul nu exista!');
  WHEN NO_JOB_FOUND THEN
    DBMS_OUTPUT.PUT_LINE('Functia nu exista!');
END ADD_JOB_HIST;
/

EXECUTE ADD_JOB_HIST(106, 'SY_ANAL');

SELECT
  *
FROM
  ISTORIC_FUNCTII
WHERE
  ID_ANGAJAT = 106;

SELECT * FROM ISTORIC_FUNCTII;

SELECT
  *
FROM
  ANGAJATI
WHERE
  ID_ANGAJAT = 106;

-- 3. In this exercise, create a program to update the minimum and maximum salaries for a job in the
-- JOBS table.
-- a. Create a stored procedure called UPD_JOBSAL to update the minimum and maximum
-- salaries for a specific job ID in the JOBS table. The procedure should provide three
-- parameters: the job ID, a new minimum salary, and a new maximum salary. Add
-- exception handling to account for an invalid job ID in the JOBS table.
-- Raise an exception if the maximum salary supplied is less than the minimum salary.
-- b. Execute the UPD_JOBSAL procedure by using a job ID of 'SY_ANAL', a minimum
-- salary of 7000 and a maximum salary of 140.
-- Note: This should generate an exception message.
-- c. Execute the UPD_JOBSAL procedure using a job ID of 'SY_ANAL', a minimum salary
-- of 7000, and a maximum salary of 14000.
-- d. Query the JOBS table to view your changes, and then commit the changes.

CREATE OR REPLACE PROCEDURE UPD_JOBSAL(
  P_JOB_ID IN FUNCTII.ID_FUNCTIE%TYPE,
  P_MIN_SAL IN FUNCTII.SALARIU_MIN%TYPE,
  P_MAX_SAL IN FUNCTII.SALARIU_MAX%TYPE
) AS
  WRONG_VALUES_FOR_SALARIES EXCEPTION;
BEGIN
  IF P_MAX_SAL < P_MIN_SAL THEN
    RAISE WRONG_VALUES_FOR_SALARIES;
  END IF;
  UPDATE FUNCTII
  SET
    SALARIU_MIN = P_MIN_SAL,
    SALARIU_MAX = P_MAX_SAL
  WHERE
    ID_FUNCTIE = P_JOB_ID;
EXCEPTION
  WHEN WRONG_VALUES_FOR_SALARIES THEN
    DBMS_OUTPUT.PUT_LINE('Salariul maxim nu poate sa fie mai mic decat cel minim!');
  WHEN NO_DATA_FOUND THEN
    DBMS_OUTPUT.PUT_LINE('Functia nu exista!');
END UPD_JOBSAL;
/

EXECUTE UPD_JOBSAL('SY_ANAL', 7000, 140);

/

EXECUTE UPD_JOBSAL('SY_ANAL', 7000, 14000);

SELECT
  *
FROM
  FUNCTII
WHERE
  ID_FUNCTIE = 'SY_ANAL';

COMMIT;

-- 4. In this exercise, create a procedure to monitor whether employees have exceeded their average
-- salaries for their job type.
-- a. In the EMPLOYEES table, add an EXCEED_AVGSAL column to store up to three
-- characters and a default value of NO.
-- Use a check constraint to allow the values YES or NO.
-- b. Write a local function called GET_JOB_AVGSAL to determine the average salary for
-- a job ID specified as a parameter. The average salary for a job is calculated from the
-- information in the JOBS table.
-- c. Write a stored procedure called CHECK_AVGSAL that checks whether each
-- employee’s salary exceeds the average salary for the JOB_ID.
-- If the employee’s salary exceeds the average for his or her job, then update the
-- EXCEED_AVGSAL column in the EMPLOYEES table to a value of YES; otherwise,
-- set the value to NO.
-- Use a cursor to select the employee’s rows using the FOR UPDATE option in the query.
-- Add exception handling to account for a record being locked.
-- Hint: The resource locked/busy error number is –54.

ALTER TABLE ANGAJATI ADD (
  EXCEED_AVGSAL CHAR(3) DEFAULT 'NO',
  CONSTRAINT EXCEED_AVGSAL_VALUES CHECK (EXCEED_AVGSAL IN('YES','NO'))
);

CREATE OR REPLACE FUNCTION GET_JOB_AVGSAL(P_JOB_ID FUNCTII.ID_FUNCTIE%TYPE) RETURN FLOAT IS
    NO_JOB_FOUND EXCEPTION;
    V_RES FLOAT;
    V_CHECK NUMBER;
  BEGIN
    SELECT COUNT(*) INTO V_CHECK FROM FUNCTII WHERE ID_FUNCTIE = P_JOB_ID;
    IF V_CHECK = 0 THEN
      RAISE NO_JOB_FOUND;
    END IF;
    SELECT (SALARIU_MIN + SALARIU_MAX) / 2 INTO V_RES FROM FUNCTII WHERE ID_FUNCTIE = P_JOB_ID;
    RETURN V_RES;
  EXCEPTION
    WHEN NO_JOB_FOUND THEN
      DBMS_OUTPUT.PUT_LINE('Functia nu exista!');
END GET_JOB_AVGSAL;

CREATE OR REPLACE PROCEDURE CHECK_AVGSAL IS
  CURSOR C IS SELECT * FROM ANGAJATI FOR UPDATE;
  e_resource_locked EXCEPTION;
  PRAGMA EXCEPTION_INIT(e_resource_locked, -54);
BEGIN
  FOR R in C LOOP
    IF (R.SALARIUL > GET_JOB_AVGSAL(R.ID_FUNCTIE)) THEN
      UPDATE ANGAJATI SET EXCEED_AVGSAL = 'YES' WHERE ID_ANGAJAT = R.ID_ANGAJAT;
    END IF;
  END LOOP;
EXCEPTION
  WHEN e_resource_locked THEN
    DBMS_OUTPUT.PUT_LINE('Resource locked');
END CHECK_AVGSAL;
/
EXECUTE CHECK_AVGSAL();
/

-- d. Execute the CHECK_AVGSAL procedure. Then, to view the results of your
-- modifications, write a query to display the employee’s ID, job, the average salary for
-- the job, the employee’s salary and the EXCEED_AVGSAL indicator column for
-- employees whose salaries exceed the average for their job, and finally commit the
-- changes.

SELECT ID_ANGAJAT, ID_FUNCTIE, GET_JOB_AVGSAL(ID_FUNCTIE), SALARIUL, EXCEED_AVGSAL FROM ANGAJATI WHERE SALARIUL > GET_JOB_AVGSAL(ID_FUNCTIE);

-- 5. Create a subprogram to retrieve the number of years of service for a specific employee.
-- a. Create a stored function called GET_YEARS_SERVICE to retrieve the total number of
-- years of service for a specific employee. The function should accept the employee ID as
-- a parameter and return the number of years of service. Add error handling to account
-- for an invalid employee ID.
-- b. Invoke the GET_YEARS_SERVICE function in a call to DBMS_OUTPUT.PUT_LINE
-- for an employee with ID 999.
-- c. Display the number of years of service for employee 106 with
-- DBMS_OUTPUT.PUT_LINE invoking the GET_YEARS_SERVICE function.
-- d. Query the JOB_HISTORY and EMPLOYEES tables for the specified employee to
-- verify that the modifications are accurate. The values represented in the results on this
-- page may differ from those you get when you run these queries.

CREATE OR REPLACE FUNCTION GET_YEARS_SERVICE(
  P_EMP_ID ANGAJATI.ID_ANGAJAT%TYPE
) RETURN NUMBER IS
  V_ANI        NUMBER;
  V_CHECK      NUMBER;
  NO_EMP_FOUND EXCEPTION;
BEGIN
  SELECT
    COUNT(*) INTO V_CHECK
  FROM
    ISTORIC_FUNCTII
  WHERE
    ID_ANGAJAT = P_EMP_ID; -- check if the emp changed job
  IF V_CHECK >= 1 THEN
    SELECT
      COUNT(*) INTO V_CHECK
    FROM
      ANGAJATI
    WHERE
      ID_ANGAJAT = P_EMP_ID; -- check if it still works
    IF V_CHECK = 1 THEN
      SELECT
        ROUND((SYSDATE - DATA_INCEPUT)/365) INTO V_ANI
      FROM
        ISTORIC_FUNCTII
      WHERE
        ID_ANGAJAT = P_EMP_ID;
      RETURN V_ANI;
    END IF;
    SELECT
      ROUND((DATA_SFARSIT - DATA_INCEPUT)/365) INTO V_ANI
    FROM
      ISTORIC_FUNCTII
    WHERE
      ID_ANGAJAT = P_EMP_ID; -- doesn't work there anymore
    RETURN V_ANI;
  END IF;
  SELECT
    COUNT(*) INTO V_CHECK
  FROM
    ANGAJATI
  WHERE
    ID_ANGAJAT = P_EMP_ID; -- didn't work before
  IF V_CHECK = 0 THEN -- no emp after all
    RAISE NO_EMP_FOUND;
  END IF;
  SELECT
    ROUND((SYSDATE - DATA_ANGAJARE)/365) INTO V_ANI
  FROM
    ANGAJATI
  WHERE
    ID_ANGAJAT = P_EMP_ID;
  RETURN V_ANI;
EXCEPTION
  WHEN NO_EMP_FOUND THEN
    DBMS_OUTPUT.PUT_LINE('Angajatul nu exista!');
END GET_YEARS_SERVICE;
/

EXECUTE DBMS_OUTPUT.PUT_LINE(GET_YEARS_SERVICE(999));

/

EXECUTE DBMS_OUTPUT.PUT_LINE(GET_YEARS_SERVICE(106));

/

SELECT
  *
FROM
  ANGAJATI
WHERE
  ID_ANGAJAT = 106;

SELECT
  *
FROM
  ISTORIC_FUNCTII
WHERE
  ID_ANGAJAT = 106;

-- 6. In this exercise, create a program to retrieve the number of different jobs that an employee
-- worked on during his or her service.
-- a. Create a stored function called GET_JOB_COUNT to retrieve the total number of
-- different jobs on which an employee worked.
-- The function should accept the employee ID in a parameter, and return the number of
-- different jobs that the employee worked on until now, including the present job.
-- Add exception handling to account for an invalid employee ID.
-- Hint: Use the distinct job IDs from the JOB_HISTORY table, and exclude the current
-- job ID, if it is one of the job IDs on which the employee has already worked. Write a
-- UNION of two queries and count the rows retrieved into a PL/SQL table. Use a FETCH
-- with BULK COLLECT INTO to obtain the unique jobs for the employee.
-- b. Invoke the function for the employee with the ID of 176.

CREATE OR REPLACE FUNCTION GET_JOB_COUNT(
  P_EMP_ID ANGAJATI.ID_ANGAJAT%TYPE
) RETURN NUMBER IS
  TYPE JOB_ID_TABLE_TYPE IS
    TABLE OF FUNCTII.ID_FUNCTIE%TYPE;
  JOB_ID_TABLE JOB_ID_TABLE_TYPE;
  JOB_COUNT    NUMBER;
BEGIN
  SELECT
    ID_FUNCTIE BULK COLLECT INTO JOB_ID_TABLE
  FROM
    (
      SELECT
        DISTINCT ID_FUNCTIE
      FROM
        ISTORIC_FUNCTII
      WHERE
        ID_ANGAJAT = P_EMP_ID UNION
        SELECT
          ID_FUNCTIE
        FROM
          ANGAJATI
        WHERE
          ID_ANGAJAT = P_EMP_ID
    );
  JOB_COUNT := JOB_ID_TABLE.COUNT;
  RETURN JOB_COUNT;
END;
/

EXECUTE DBMS_OUTPUT.PUT_LINE(GET_JOB_COUNT(176));

-- example application exception

DECLARE
  my_error EXCEPTION;
  PRAGMA EXCEPTION_INIT(my_error, -20001);
BEGIN
  RAISE_APPLICATION_ERROR(-20001, 'This is a custom error message.');
END;
/