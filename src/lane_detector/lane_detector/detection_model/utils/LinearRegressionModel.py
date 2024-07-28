
class LinearRegressionModel:


    def get_best_fit(lines):
        """
        Returns the slope and the y intercept given a list of points defined as lines

            Parameters:
                lines: array of lines in the format: x1, y1, x2, y2

            Returns:
                slope: slope of the linear regression
                y_intercept: y intercept of the line
        """

        slope = 0
        y_intercept = 0

        n = len(lines) * 2

        sum_x = 0
        sum_y = 0
        sum_xy = 0
        sum_x_squared = 0

        for line in lines:
            for x1, y1, x2, y2 in line:
                sum_x += x1 + x2
                sum_y += y1 + y2

                sum_xy += (x1 * y1) + (x2 * y2)
                sum_x_squared += (x1 * x1) + (x2 * x2)

        slope = ((n * sum_xy) - (sum_x * sum_y)) / ((n * sum_x_squared) - (sum_x * sum_x))
        y_intercept = (sum_y - (slope * sum_x)) / n

        return slope, y_intercept
            
