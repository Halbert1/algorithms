def func(array):
    if len(array) <= 2:
        return 0
    left = 0
    maxLeft = array[left]
    right = len(array) - 1
    maxRight = array[right]
    volume = 0
    while left < right:
        if maxLeft <= maxRight:   # from left to right
            left += 1
            if maxLeft > array[left]:
                volume += maxLeft - array[left]
            else :
                maxLeft = array[left]
        else:
            right -= 1
            if maxRight > array[right]:
                volume += maxRight - array[right]
            else:
                maxRight = array[right]
    return volume


print func([0, 1])
print func([0, 1, 0, 1])
print func([0, 9, 3, 7, 8, 10, 16, 5, 19,11, 0, 5])
