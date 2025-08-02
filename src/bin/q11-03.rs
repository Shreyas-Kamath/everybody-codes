use std::{
    collections::HashMap,
    fs::File,
    io::{BufRead, BufReader},
    time::Instant,
};

fn sim(termite_map: &HashMap<&str, Vec<&str>>, parent: &str, days: i32) -> i64 {
    let mut termite_counts: HashMap<&str, i64> = HashMap::with_capacity(64);
    termite_counts.insert(parent, 1);

    for _ in 0..days {
        let mut new_counts: HashMap<&str, i64> = HashMap::with_capacity(64);

        for (termite, &count) in &termite_counts {
            for &child in &termite_map[termite] {
                *new_counts.entry(child).or_insert(0) += count;
            }
        }

        termite_counts = new_counts; // safe move
    }

    termite_counts.values().sum()
}

fn main() {
    let start = Instant::now();
    let reader = BufReader::new(File::open("data.txt").unwrap());

    let mut termite_map: HashMap<&str, Vec<&str>> = HashMap::with_capacity(64);
    let mut lines: Vec<String> = Vec::with_capacity(64);

    for line in reader.lines() {
        lines.push(line.unwrap());
    }

    for line in &lines {
        let (parent, children) = line.split_once(':').unwrap();
        let child_list: Vec<&str> = children.split(',').collect();
        termite_map.insert(parent, child_list);
    }

    let days = 20;
    let mut min_pop = i64::MAX;
    let mut max_pop = i64::MIN;

    for &parent in termite_map.keys() {
        let pop = sim(&termite_map, parent, days);
        min_pop = min_pop.min(pop);
        max_pop = max_pop.max(pop);
    }

    println!("{:.2?}", start.elapsed());
    println!("{}", max_pop - min_pop);
}
