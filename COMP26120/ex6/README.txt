This is some advice on how to use data.zip

The data folder contains the same data three times (sorry for the redundancy). In each folder there are 9 sets of data of varying size. The input data is labelled 'in' and the expected answer is labelled 'ans'.

To run with 'in' you should run

./sort < in

and to test you get the right result you can run

./sort < in | diff ans -

To run across all files in a directory you could try something like

for f in dir/*; do time ./sort < $f/in; done
