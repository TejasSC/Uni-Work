START /opt/info/courses/COMP23111/create-Eclectic-Ecommerce-tables.sql
START /opt/info/courses/COMP23111/populate-Eclectic-Ecommerce-tables.sql
-- COMP23111 Fundamentals of Databases
-- Exercise 04
-- by Tejas Chandrasekar, ID 10136960, login name MBAXATC4
-- causes the SQL statements themselves to be spooled
SET ECHO ON
SPOOL '/home/mbaxatc4/COMP23111/ex4/EX04-10136960.log'
-- sends everything to <spoolfilename>
------------------------------------Part 1------------------------------------
-- a) view showing first and last names of customers
-- O is orders in one shopping cart, s is shipped | empty shopping carts
CREATE OR REPLACE VIEW customers_with_some_carts AS
SELECT DISTINCT firstName, lastName
FROM customerInfo NATURAL JOIN orderCartInfo
WHERE customerInfo.loginName = orderCartInfo.customerID;
SELECT * FROM customers_with_some_carts;

-- b) view = code, item number, category id and quantity in stock of inventory
-- items
CREATE OR REPLACE VIEW inventory_items_reordered AS
SELECT code, itemNum, qtyInstock, categoryId
FROM inventoryItem NATURAL JOIN category
WHERE itemNum IN (
  SELECT itemNum
  FROM itemType
  WHERE itemType.belongsTo IN (
    SELECT categoryId
    FROM category
  )
)
AND qtyInstock < 25;
SELECT * FROM inventory_items_reordered;

-- c) loginName, first and last names, order cart id, total order price
CREATE OR REPLACE VIEW names_with_total_order_prices AS
SELECT lineItems.orderCartId, loginName, firstName, lastName, SUM(qtyOrdered*orderPrice) AS totalOP
FROM customerInfo INNER JOIN orderCartInfo
ON customerInfo.loginName = orderCartInfo.customerID
INNER JOIN lineItems
ON orderCartInfo.orderCartId = lineItems.orderCartId
GROUP BY lineItems.orderCartId, loginName, firstName, lastName;
SELECT * FROM names_with_total_order_prices;

-- d) loginName, first and last names, total of all orders by a customer
CREATE OR REPLACE VIEW names_with_customer_TOPs AS
SELECT loginName, firstName, lastName, SUM(orderPrice*qtyOrdered) AS sumOP
FROM customerInfo INNER JOIN orderCartInfo
ON customerInfo.loginName = orderCartInfo.customerID
INNER JOIN lineItems
ON orderCartInfo.orderCartId = lineItems.orderCartId
GROUP BY loginName, firstName, lastName;
SELECT * FROM names_with_customer_TOPs;

-- e) view returns number of parts per customer
-- use it to return outcomes such as 'BR-1 satisfied' or 'BR-1 violated'
CREATE OR REPLACE VIEW total_carts_per_customer AS
SELECT DISTINCT customerID, COUNT(customerID) AS numCarts
FROM orderCartInfo
GROUP BY customerID;
SELECT customerID, numCarts,
CASE
     WHEN numCarts > 2 THEN 'BR-1 violated'
     ELSE 'BR-1 satisfied'
END
FROM total_carts_per_customer;

-- f) query nesting - should return 2 rows i think
SELECT itemNum, itemSize, itemColor, numThisColorSize
FROM (
  SELECT itemNum, itemSize, itemColor, numThisColorSize,
  CASE
      WHEN numThisColorSize > 1 THEN 'BR-2 violated'
      ELSE 'BR-2 satisfied'
  END AS br2Status
  FROM (
    SELECT itemNum, itemSize, itemColor, COUNT(itemNum) AS numThisColorSize
    FROM inventoryItem
    GROUP BY itemNum, itemSize, itemColor))
WHERE br2Status = 'BR-2 violated';

-- g) Trigger that raises an error if price of item set to value > 4*cheapest
-- priced item
CREATE OR REPLACE TRIGGER priceNotTooHighTrigger
BEFORE INSERT OR UPDATE ON itemType
FOR EACH ROW
DECLARE
  highestPrice number;
BEGIN
  SELECT min(4*price) INTO highestPrice FROM itemType;
  IF :new.price > highestPrice THEN
    raise_application_error(-20000, 'Price too much');
  END IF;
END;
/

SELECT * FROM itemType;
-- Both statements cause trigger to go off
INSERT INTO itemType VALUES ('D2', 'The Expectant Mirror', '^-^', 45.99, 'H');
SELECT * FROM itemType;
UPDATE itemType
SET price = 45.99
WHERE itemNum = 'A0';
SELECT * FROM itemType;

SPOOL OFF
START /opt/info/courses/COMP23111/drop-Eclectic-Ecommerce-tables.sql;
DROP VIEW customers_with_some_carts;
DROP VIEW inventory_items_reordered;
DROP VIEW names_with_total_order_prices;
DROP VIEW names_with_customer_TOPs;
DROP VIEW total_carts_per_customer;
