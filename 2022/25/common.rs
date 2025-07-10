use std::fmt;
use std::ops;
use std::cmp;

pub struct Snafu {
    d: Vec<i8>
}

impl Snafu {
    const DIGITS: [char; 5] = ['=', '-', '0', '1', '2'];

    fn digit_to_i8(c: char) -> i8 {
        for i in 0..5 {
            if c == Snafu::DIGITS[i] { return i as i8 - 2; }
        }
        panic!("Invalid Snafu digit '{}'", c);
    }

    fn i8_to_digit(i: i8) -> char {
        if i < -2 || i > 2 {
            panic!("Invalid Snafu digit value {}", i);
        }
        Snafu::DIGITS[(i + 2) as usize]
    }

    pub fn ndigits(&self) -> usize {
        self.d.len()
    }

    pub fn zero() -> Snafu {
        Snafu { d: vec![0] }
    }

    pub fn from_str(s: &str) -> Snafu {
        let mut d = vec![];
        for c in s.chars() { d.push(Self::digit_to_i8(c)); }
        d.reverse();
        Snafu { d }
    }
}

impl fmt::Display for Snafu {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        // Strip leading zeros
        let mut n = self.ndigits()-1;
        while self.d[n] == 0 { n -= 1; }

        for i in (0..=n).rev() {
            write!(f, "{}", Self::i8_to_digit(self.d[i]))?;
        }
        Ok(())
    }
}

impl ops::AddAssign<&Snafu> for Snafu {
    fn add_assign(&mut self, other: &Snafu) {
        for i in 0..cmp::max(self.ndigits(), other.ndigits()) {
            if i < other.ndigits() {
                self.d[i] += other.d[i];
            }

            // Carry over, both ways
            if i == self.ndigits()-1 { self.d.push(0); }
            while self.d[i] > 2  { self.d[i+1] += 1; self.d[i] -= 5; }
            while self.d[i] < -2 { self.d[i+1] -= 1; self.d[i] += 5; }
        }

        for i in 0..self.ndigits() {
            if self.d[i] == 0 { self.d.pop(); } else { break; }
        }
    }
}
