all: generateHashTable generateHashTableBinOrdered generateBinDataSet

generateHashTable: generateHashTable.c
	gcc -o generateHashTable generateHashTable.c

generateHashTableBinOrdered: generateHashTableBinOrdered.c
	gcc -o generateHashTableBinOrdered generateHashTableBinOrdered.c

generateBinDataSet: generateBinDataSet.c
	gcc -o generateBinDataSet generateBinDataSet.c

run: run-generateHashTable run-generateHashTableBinOrdered run-generateBinDataSet

run-generateHashTable: generateHashTable
	./generateHashTable

run-generateHashTableBinOrdered: generateHashTableBinOrdered
	./generateHashTableBinOrdered	

run-generateBinDataSet: generateBinDataSet
	./generateBinDataSet