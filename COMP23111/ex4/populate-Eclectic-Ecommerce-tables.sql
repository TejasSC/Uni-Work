
insert into customerInfo values ('choizeznyc', 'KJH*GS9', 'John', 'Booker', 'jb@choizez-nyc.com', '202 East 78th', 'NY', '10021');
insert into customerInfo values ('shkeandco', 'JHKG*!9S', 'Mary', 'Folio', 'mf@shkeandco.com', '993 Lexington Ave', 'NY', '10065');
insert into customerInfo values ('dramab', 'KG454*56Skl', 'Ophelia', 'Elsinore', 'oe@dramab.com', '502 West 40th', 'NY', '10018');
insert into customerInfo values ('astrab', '4!2!3kjn3e', 'Percy', 'Byron', 'pb@astrab.com', '92 31st', 'NY', '11106');

insert into orderCartInfo values ('1', 'S', 2015, 12, 23, 'shkeandco');
insert into orderCartInfo values ('2', 'S', 2015, 08, 03, 'dramab');
insert into orderCartInfo values ('3', 'S', 2015, 12, 23, 'astrab');
insert into orderCartInfo values ('4', 'O', 2015, 08, 03, 'astrab');
insert into orderCartInfo values ('5', 'S', 2015, 09, 18, 'shkeandco');
insert into orderCartInfo values ('6', 'S', 2015, 06, 03, 'shkeandco');
insert into orderCartInfo values ('7', 'S', 2015, 12, 12, 'dramab');
insert into orderCartInfo values ('8', 'O', 2015, 08, 28, 'astrab');

insert into category values ('F',  'fiction');
insert into category values ('H',  'history');
insert into category values ('P',  'poetry');
insert into category values ('C',  'crime');
insert into category values ('SF', 'sci-fi');

insert into itemType values ('A0', 'The Anarchy of Mask', '***', 10.99, 'P');
insert into itemType values ('A1', 'The Butler Did', '---', 11.99, 'C');
insert into itemType values ('A2', 'The Abolished Man', '===', 15.99, 'SF');
insert into itemType values ('A3', 'Lyrical Bullets', '+-+-', 20.99, 'P');
insert into itemType values ('B1', 'The Postlude', '=\=\=', 34.99, 'P');
insert into itemType values ('C1', 'The August of Guns', '**--', 10.99, 'H');
insert into itemType values ('C2', 'The Expectant Mirror', '^-^', 12.99, 'H');

insert into inventoryItem values ('A0', 'pbk', 30, 'black', 3.0);
insert into inventoryItem values ('B1', 'hbk', 50, 'white', 4.0);
insert into inventoryItem values ('A0', 'hbk', 25, 'green', 4.0);
insert into inventoryItem values ('C2', 'hbk', 20, 'black', 3.0);
insert into inventoryItem values ('C1', 'ebk', 70, 'black', 4.0);
insert into inventoryItem values ('A3', 'pbk', 30, 'black', 2.0);
insert into inventoryItem values ('A2', 'pbk', 50, 'green', 3.0);
insert into inventoryItem values ('A0', 'ebk', 15, 'green', 4.0);
insert into inventoryItem values ('C2', 'pbk', 30, 'black', 3.0);

insert into lineItems values ('1', 'A0', 'pbk', 1, 2.99);
insert into lineItems values ('8', 'A3', 'pbk', 2, 3.99);
insert into lineItems values ('3', 'A2', 'pbk', 5, 5.99);
insert into lineItems values ('2', 'A2', 'pbk', 3, 3.99);
insert into lineItems values ('1', 'C1', 'ebk', 2, 2.99);
insert into lineItems values ('3', 'C2', 'hbk', 4, 2.99);
insert into lineItems values ('3', 'A3', 'pbk', 8, 3.99);
insert into lineItems values ('4', 'B1', 'hbk', 3, 4.99);
insert into lineItems values ('6', 'B1', 'hbk', 2, 6.99);
insert into lineItems values ('5', 'A2', 'pbk', 1, 2.99);
insert into lineItems values ('7', 'A1', 'pbk', 1, 1.99);
