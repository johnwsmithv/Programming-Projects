/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package java.banking.application;

/**
 *
 * @author Johnny V
 */
public class Bank {
    private long accountBalance;
    private long depositMoney;
    private long withdrawMoney;
    private long takeOutLoan;
    public Bank(long accountBalance, long depositMoney, long withdrawMoney, long takeOutLoan) {
        accountBalance = this.accountBalance;
        depositMoney = this.depositMoney;
        withdrawMoney = this.withdrawMoney;
        takeOutLoan = this.takeOutLoan;
    }
    public void setAccountBalance(long startingAmount){
        accountBalance = startingAmount;
    }
    public long  getAccountBalance(){
        return accountBalance;
    }
    public static void main(String args[]){
        
    }
}
