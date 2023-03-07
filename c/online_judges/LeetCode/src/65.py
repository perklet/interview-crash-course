class Solution:
    # @param {string} s
    # @return {boolean}
    def isNumber(self, s):
        BEFORE = 0 # before dot
        AFTER = 1 # after dot
        EXP = 2 # after e
        phase = BEFORE
        allow_sign = True
        
        s = s.strip()
        
        if not any([c.isdigit() for c in s]):
            return False
        
        if s == '' or s[0] == 'e' or s[-1] == 'e' or s == '.':
            return False
        if s[0] == '.' and s[1] == 'e':
            return False
        if s[0] == '-' and s[1] == 'e':
            return False
        
        for c in s:
            if '0' <= c <= '9':
                allow_sign = False
                pass
            elif c == '.':
                allow_sign = False
                if phase == EXP or phase == AFTER:
                    return False
                else:
                    phase = AFTER
            elif c == 'e':
                if phase == EXP:
                    return False
                allow_sign = True
                phase = EXP
                
            elif c == '-' or c == '+':
                if not allow_sign:
                    return False
                allow_sign = False
            else:
                return False
        
        return s[-1].isdigit() if phase == EXP else True
