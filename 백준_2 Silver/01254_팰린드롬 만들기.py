
def ifPalindrome(string: str):
    left = len(string) // 2
    right = len(string) // 2
    if len(string) % 2 == 0:
        left -= 1
    
    while left >= 0:
        if string[left] != string[right]:
            return False
        
        left -= 1
        right += 1
    
    return True

S = input()

ans = -1
for i in range(len(S)):
    if ifPalindrome(S[i:]):
        ans = len(S) + i
        break

print(ans)