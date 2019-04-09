START /opt/info/courses/COMP23111/create-University-tables.sql
START /opt/info/courses/COMP23111/populate-University-tables.sql
START /opt/info/courses/COMP23111/create-Accident-tables.sql
START /opt/info/courses/COMP23111/populate-Accident-tables.sql
-- COMP23111 Fundamentals of Databases
-- Exercise 03
-- by Tejas Chandrasekar, ID 10136960, login name MBAXATC4
-- causes the SQL statements themselves to be spooled
SET ECHO ON
SPOOL '/home/mbaxatc4/COMP23111/ex3/EX03-10136960.log'
-- sends everything to <spoolfilename>
------------------------------------Part 1a------------------------------------
-- i) All unique names of students who have taken >= 1 CS course
SELECT DISTINCT name FROM student
WHERE student.ID IN (SELECT DISTINCT ID FROM takes
                       WHERE takes.course_id LIKE 'CS%');

-- ii) all names and IDs of students who haven't taken course before < 2009
SELECT ID, name FROM student
WHERE student.ID IN (SELECT DISTINCT ID FROM takes
                        WHERE takes.year > 2009);

-- iii) Maximum salaries of instructors in each department
SELECT MAX(salary), instructor.dept_name
FROM instructor
GROUP BY dept_name;

-- iv) Smallest of part iii)
SELECT MIN(salary), instructor.dept_name
FROM instructor
GROUP BY dept_name
HAVING MIN(salary) = (SELECT MIN(MAX(salary))
                      FROM instructor
                      GROUP BY dept_name);
------------------------------------Part 1b------------------------------------
-- i) new CS-001 course in compsci, Weekly Seminar, 10 credits
INSERT INTO course VALUES ('CS-001', 'Weekly Seminar', 'Comp. Sci.', 10);
-- ii) new CS-002 course in compsci, monthly seminar, 0 credits
-- INSERT INTO course VALUES ('CS-002', 'Weekly Seminar', 'Comp. Sci.', 0);
-- ERROR at line 1:
-- ORA-02290: check constraint (MBAXATC4.SYS_C001299534) violated
-- iii) not possible to have a course with 0 credits since 'check (credits > 0)'
-- exists in the create table definition
-- iv) not enough columns
INSERT INTO section(course_id, sec_id, semester, YEAR)
VALUES ('CS-001', '1', 'Fall', 2009);
-- v) missing surname of student of course, student id, and grade
-- must parameterize it by selecting specific columns
-- vi) enrol every student in CS department in above new section
--following attributes of takes are part of primary key
INSERT INTO takes(ID, course_id, sec_id, semester, YEAR)
SELECT ID, 'CS-001', '1', 'Fall', 2009 FROM student
WHERE dept_name = 'Comp. Sci.';
-- vii) Deleting everything from above course where student's name is Zhang
DELETE FROM takes
WHERE course_id = 'CS-001' AND sec_id = '1' AND semester = 'Fall' AND YEAR = 2009
AND ID IN (SELECT ID FROM student WHERE student.name = 'Zhang');
-- viii) Delete all takes tuples which are course with database as a title
DELETE FROM takes
WHERE course_id IN (SELECT course_id
                    FROM course
                    WHERE lower(course.title) LIKE '%database%');
-- ix) Delete course CS-001
DELETE FROM takes
WHERE course_id = 'CS-001';
-- x) course_id is a valid attribute therefore the above statement does as intended
------------------------------------Part 2a------------------------------------
-- i) Find number of acciedents in which Jane Rowling's cars were involved
SELECT COUNT(driver_id)
FROM participated
WHERE license IN (SELECT license
                  FROM owns
                  WHERE driver_id IN (SELECT driver_id
                                      FROM person
                                      WHERE person.name = 'Jane Rowling'));
-- ii) Update the amount of damage for car with license number KUY 629
UPDATE participated
SET damage_amount = 2500
WHERE report_number = 7897423 AND license = 'KUY 629';
-- iii) list name of people who participated in accidents along with total
-- damage caused, but only include those whose total damage > 3000
SELECT name, SUM(damage_amount)
FROM person NATURAL JOIN participated
GROUP BY person.name
HAVING SUM(damage_amount) > 3000
ORDER BY SUM(damage_amount) DESC;
-- iv) Create view returning locations where accidents happened along with avg damage
CREATE VIEW average_damage_per_location AS
SELECT location, AVG(damage_amount) AS avgdmg
FROM accident NATURAL JOIN participated
GROUP BY location;
-- accessible with
-- v) use average_damage_per_location to find location with highest avg damage
SELECT location
FROM average_damage_per_location
WHERE avgdmg = (SELECT MAX(avgdmg)
                FROM average_damage_per_location);

SPOOL OFF
START /opt/info/courses/COMP23111/drop-University-tables.sql;
START /opt/info/courses/COMP23111/drop-Accident-tables.sql;
drop view average_damage_per_location;
