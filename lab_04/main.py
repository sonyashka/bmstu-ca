import random
import numpy as np
import matplotlib.pyplot as plt
from math import sin

class Coefficient():
    def __init__(self):
        self.xCoef = []
        self.yCoef = []

    def primeCoefCulc(self, data):
        for i in range(data.n + 1):
            self.xCoef.append([])

        for i in range(data.n + 1):
            for j in range(i, data.n + 1):
                curCoef = 0
                for k in range(data.count):
                    curCoef += data.p[k] * pow(data.x[k], i + j)
                self.xCoef[i].append(curCoef)
                if i < j:
                    self.xCoef[j].append(curCoef)

        for i in range(data.n + 1):
            curCoef = 0
            for j in range(data.count):
                curCoef += data.p[j] * data.y[j] * pow(data.x[j], i)
            self.yCoef.append(curCoef)

        self.npXCoef = np.asarray(self.xCoef)
        self.npYCoef = np.asarray(self.yCoef)

        self.npResCoef = np.linalg.solve(self.npXCoef, self.npYCoef)

        # for i in range(len(self.npResCoef)):
        #     print("a[{0:3d}] = {1:6.3f}".format(i, self.npResCoef[i]))

class Data():
    def __init__(self):
        self.count = 20
        self.x = []
        self.y = []
        self.p = []
        self.n = 0
        self.nBuf = 0

        for i in range(self.count):
            self.x.append(random.uniform(0, 10))
        self.x.sort()

        for i in range(self.count):
            self.y.append(self.x[i] + sin(self.x[i]))
            self.p.append(random.uniform(0.01, 20))

    def inputAll(self):
        self.__init__()
        self.output()
        print("Do you want to choose weights? [y/1/n] ", end = '')
        changeF = input()
        if changeF == 'y':
            self.weightsChange()
            self.output()
        elif changeF == '1':
            for i in range(self.count):
                self.p[i] = 1
            self.output()
        self.inputN()

    def inputN(self):
        print("Input n: ", end = '')
        self.n = int(input())

    def output(self):
        print(" ind |      x     |       y    |       p")
        print('-' * 44)
        for i in range(self.count):
            print("{0:4d} | {1:10.3f} | {2:10.3f} | {3:10.3f}".format(i, self.x[i], self.y[i], self.p[i]))

    def weightsChange(self):
        ind = 0
        while (ind != -1):
            print("Input index and value: ", end = '')
            ind = int(input())
            if ind != -1:
                value = float(input())
                self.p[ind] = value
        print("End of changes!")

    def drawFunc(self, coef, mode):
        self.plotRealFunc()
        if mode == 1:
            print("mode = 1")
            self.nBuf = self.n
            self.n = 1
            coef.__init__()
            coef.primeCoefCulc(data)
            self.plotFunc(coef, mode)
            mode = 0
            print("mode = 0")
            self.n = 2
            coef.__init__()
            coef.primeCoefCulc(data)
            self.plotFunc(coef, mode)
            plt.plot(self.x, self.y, 'o')
            plt.xlabel("X")
            plt.ylabel("Y")
            plt.grid()
            plt.title("Наилучшее среднеквадртичное приближение")
            plt.legend()
            plt.show()
        else:
            print("mode = 2")
            self.n = self.nBuf
            coef.__init__()
            coef.primeCoefCulc(data)
            self.plotFunc(coef, mode)
            mode = 3
            print("mode = 3")
            for i in range(self.count):
                self.p[i] = 1
            coef.__init__()
            coef.primeCoefCulc(data)
            self.plotFunc(coef, mode)
            plt.plot(self.x, self.y, 'o')

            plt.xlabel("X")
            plt.ylabel("Y")
            plt.grid()
            plt.title("Наилучшее среднеквадртичное приближение")
            plt.legend()
            plt.show()

    def plotRealFunc(self):
        xBuf = np.linspace(self.x[0], self.x[self.count - 1], 1000)
        yBuf = []
        for i in range(len(xBuf)):
            yBuf.append(xBuf[i] + sin(xBuf[i]))
        plt.plot(xBuf, yBuf, color = "m", label = "Исходная функция")

    def plotFunc(self, coef, mode):
        xBuf = np.linspace(self.x[0], self.x[self.count - 1], 1000)
        yBuf = []
        for i in range(len(xBuf)):
            yCur = coef.npResCoef[0]
            for j in range(1, self.n + 1):
                yCur += coef.npResCoef[j] * pow(xBuf[i], j)
            yBuf.append(yCur)
        
        if mode == 0:
            plt.plot(xBuf, yBuf, color = "r", label = "Равные весы (n={0})".format(self.n))
        elif mode == 1:
            plt.plot(xBuf, yBuf, color = "g", label = "Равные веса (n={0})".format(self.n))
        elif mode == 2:
            plt.plot(xBuf, yBuf, color = "b", label = "Разные веса (n={0})".format(self.n))
        else:
            plt.plot(xBuf, yBuf, color = "y", label = "Веса равны 1 (n={0})".format(self.n))

if __name__ == "__main__":
    data = Data()
    data.inputAll()
    coef = Coefficient()
    coef.__init__()
    coef.primeCoefCulc(data)

    data.drawFunc(coef, 1)
    data.drawFunc(coef, 2)