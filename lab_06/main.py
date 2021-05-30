from math import pow

class Differentiate:
    def __init__(self):
        self.h = 1.0
        self.x = [1, 2, 3, 4, 5, 6]
        self.y = [0.571, 0.889, 1.091, 1.231, 1.333, 1.412]
        self.y1 = [0 for i in range(6)]
        self.y2 = [0 for i in range(6)]
        self.y3 = [0 for i in range(6)]
        self.y4 = [0 for i in range(6)]
        self.y5 = [0 for i in range(6)]

    def output(self):
        print("  x  |   y   |     1    |     2    |     3    |     4    |     5")
        print("-" * 70)
        for i in range(6):
            print("  {0}  |{1:7.3f}|{2:10.3f}|{3:10.3f}|{4:10.3f}|{5:10.3f}|{6:10.3f}".format(self.x[i], self.y[i], self.y1[i], self.y2[i], self.y3[i], self.y4[i], self.y5[i]))
    
    def calc(self):
        self.leftDif()
        self.centerDif()
        self.secondRungeDif(1)
        self.alignedCoeffsDif()
        self.secondLeftDif()

    def leftDif(self):
        for i in range(len(self.y)):
            if i == 0:
                self.y1[i] = 0.0
            else:
                self.y1[i] = (self.y[i] - self.y[i - 1]) / self.h

    def centerDif(self):
        for i in range(len(self.y)):
            if i == 0 or i == len(self.y) - 1:
                self.y2[i] = 0.0
            else:
                self.y2[i] = (self.y[i + 1] - self.y[i - 1]) / 2 * self.h

    def secondRungeDif(self, p):
        yTmp = []
        for i in range(len(self.y)):
            if i < 2:
                yTmp.append(0)
            else:
                yTmp.append((self.y[i] - self.y[i - 2]) / (2 / self.h))

        for i in range(len(self.y1)):
            if i < 2:
                self.y3[i] = 0.0
            else:
                self.y3[i] = self.y1[i] + (self.y1[i] - yTmp[i]) / (pow(2, p) - 1)
    
    def alignedCoeffsDif(self):
        for i in range(len(self.y)):
            if i == len(self.y) - 1:
                self.y4[i] = 0.0
            else:
                k = pow(self.y[i], 2) / pow(self.x[i], 2)
                self.y4[i] = k * (((-1.0 / self.y[i + 1]) - (-1.0 / self.y[i])) / ((-1.0 / self.x[i + 1]) - (-1.0 / self.x[i])))

    def secondLeftDif(self):
        for i in range(len(self.y)):
            if i == 0 or i == len(self.y) - 1:
                self.y5[i] = 0.0
            else:
                self.y5[i] = (self.y[i - 1] - 2 * self.y[i] + self.y[i + 1]) / pow(self.h, 2)

if __name__ == "__main__":
    print("Lets start!")
    calc = Differentiate()
    calc.__init__()
    calc.calc()
    calc.output()