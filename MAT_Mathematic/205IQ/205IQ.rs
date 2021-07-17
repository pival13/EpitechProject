#![allow(non_snake_case)]

fn normalLaw(aver: f64, dev: f64, x: f64) -> f64 {
    let a = 2.0_f64*std::f64::consts::PI;
    let b = x-aver;
    let c = -b.powi(2)/(2_f64*dev.powi(2));

    return 1.0 / (dev * a.sqrt()) * c.exp()
}

fn integralNormalLaw(aver: f64, dev: f64, min: f64, max: f64) -> f64 {
    let n = (max as i64) * 200;
    let delta = (max-min)/(n as f64);
    let mut r = 0_f64;

    for i in 0..=n {
        if i == 0 || i == n {
            r += normalLaw(aver, dev, min + (i as f64)*delta);
        } else if i % 2 == 1 {
            r += 4_f64 * normalLaw(aver, dev, min + (i as f64)*delta);
        } else {
            r += 2_f64 * normalLaw(aver, dev, min + (i as f64)*delta);
        }
    }
    return r * delta / 3_f64;
}

fn main() {
    let mut args = std::env::args();
    if args.len() < 3 || args.len() > 5 { println!("USAGE\n\t./205IQ average deviation [IQ1] [IQ2]"); std::process::exit(84) }

    let averageP = args.nth(1).expect("").parse::<f64>();
    let devP = args.nth(0).expect("").parse::<f64>();
    if !averageP.is_ok() || !devP.is_ok() { println!("USAGE\n\t./205IQ average deviation [IQ1] [IQ2]"); std::process::exit(84) }

    let aver = averageP.unwrap();
    let dev = devP.unwrap();
    if aver < 0_f64 || aver > 200_f64 || dev <= 0_f64 { println!("USAGE\n\t./205IQ average deviation [IQ1] [IQ2]"); std::process::exit(84) }

    if args.len() == 0 {
        for i in 0..201 {
            println!("{} {:.05}", i, normalLaw(aver, dev, i as f64));
        }
    } else if args.len() == 1 {
        let IQ1P = args.nth(0).expect("").parse::<i32>();
        if !IQ1P.is_ok() { println!("USAGE\n\t./205IQ average deviation [IQ1] [IQ2]"); std::process::exit(84) }

        let IQ1 = IQ1P.unwrap();
        if IQ1 < 0 || IQ1 > 200 { println!("USAGE\n\t./205IQ average deviation [IQ1] [IQ2]"); std::process::exit(84) }

        println!("{:.01}% of people have an IQ inferior to {}", integralNormalLaw(aver, dev, 0_f64, IQ1 as f64) * 100_f64, IQ1)
    } else if args.len() == 2 {
        let IQ1P = args.nth(0).expect("").parse::<i32>();
        let IQ2P = args.nth(0).expect("").parse::<i32>();
        if !IQ1P.is_ok() || !IQ2P.is_ok() { println!("USAGE\n\t./205IQ average deviation [IQ1] [IQ2]"); std::process::exit(84) }

        let IQ1 = IQ1P.unwrap();
        let IQ2 = IQ2P.unwrap();
        if IQ1 < 0 || IQ1 > 200 || IQ2 < 0 || IQ2 > 200 || IQ1 >= IQ2 { println!("USAGE\n\t./205IQ average deviation [IQ1] [IQ2]"); std::process::exit(84) }

        println!("{:.01}% of people have an IQ between {} and {}", integralNormalLaw(aver, dev, IQ1 as f64, IQ2 as f64) * 100_f64, IQ1, IQ2)
    }
}