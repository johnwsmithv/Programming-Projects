func dynamicFibSequence(_ fib : Int) -> [Int] {
    var fibArray : [Int] = [0, 1]
    for i in 2...fib{
        fibArray.append(fibArray[i - 1] + fibArray[i - 2])
    }
    return fibArray
}

print(dynamicFibSequence(50))

func recurFibSequence(_ fib : Int) -> Int { 
    // var fibArray : [Int] = [0, 1]
    if(fib <= 1){
        return 1
    }
    return recurFibSequence(fib - 1) + recurFibSequence(fib - 2)
}

print(recurFibSequence(5))