/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package fun.projects;

/**
 *
 * @author Johnny V
 */
public class binarySearch {
    int [] primes = new int[]{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    double primeToBeFound;
    double numberOfIterations = 0;
    double searchPrimeArray = primes.length / 2;
    public binarySearch(double primeToBeFound) {
        this.primeToBeFound = primeToBeFound;
    }
    public double binarySearchAlgorithm(){
        System.out.println("prime to be found: " + primeToBeFound);
        for(double i = 0; i < primes.length; i++){
            searchPrimeArray = Math.floor((i + primes.length) / 2);
            System.out.println("Prime Index: " + searchPrimeArray);
            if(primes[searchPrimeArray] < primeToBeFound){
                i = searchPrimeArray;
            }
            else if(primes[searchPrimeArray] == primeToBeFound){
                System.out.println("WE made it in!");
                break;
            }
            System.out.println(numberOfIterations);
            numberOfIterations++;
        }
        return numberOfIterations;
    }
}

