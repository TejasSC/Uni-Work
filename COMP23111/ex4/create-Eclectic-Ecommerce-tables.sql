create table customerInfo (
       loginName varchar(10) primary key,
       password	 varchar(15) not null,
       firstName varchar(20) not null,
       lastName	 varchar(20) not null,
       email	 varchar(20) not null,
       cStreet	 varchar(20) not null,
       cState	 varchar(2) not null,
       cZip	 varchar(6) not null
);

create table orderCartInfo (
       orderCartId varchar(10) primary key,
       oType	   varchar(15) not null check (oType in ('S', 'O')),
       oYear 	   int	       not null,
       oMonth	   int	       not null,
       oDay	   int	       not null,
       customerID  varchar(10) not null
       		   references customerInfo(loginName) on delete cascade
);

create table category (
       categoryId  varchar(10) primary key,
       description varchar(50)
);

create table itemType (
       itemNum   varchar(10) primary key,
       name	 varchar(20) not null,
       picture 	 varchar(50),
       price	 float	     not null,
       belongsTo varchar(10) not null
       		 references category(categoryId) on delete cascade
);

create table inventoryItem (
       itemNum    varchar(10) not null
       		  references itemType(itemNum) on delete cascade,
       code	  varchar(20) not null,
       qtyInstock float	      not null,
       itemColor  varchar(15),
       itemSize	  float,
       primary key (itemNum, code)
);

create table lineItems (
       orderCartId varchar(10) not null
       		   references orderCartInfo(orderCartId) on delete cascade,
       itemNum     varchar(10) not null
       		   references itemType(itemNum) on delete cascade,
       code	   varchar(20) not null,
       qtyOrdered  float       not null,
       orderPrice  float       not null,
       primary key (orderCartId, itemNum, code)
);
