mod acc_recorder;
mod test_file;
// use acc_recorder::record_start;
use test_file::create_test_file;
use clap::Arg;
fn main() {
    let cmd = clap::Command::new("Telemetry Recorder")
    .subcommand_required(true)
    .subcommand(clap::Command::new("ACC")
        .about("Records ACC Telemetry")
        .arg(Arg::new("frequence"))
        .arg(Arg::new("rateFullFrame"))
        .arg(Arg::new("output").short('o').required(true)))
    .subcommand(clap::Command::new("Test")
        .about("Creates a Test File")
        .arg(Arg::new("output").short('o').required(true))
        .arg(Arg::new("laps").required(true))
        .arg(Arg::new("dataPerLap").required(true)));
    let matches = cmd.get_matches();
    
    match matches.subcommand() {
        Some(("ACC",matches)) => {
            //record_start();
        },
        Some(("Test",matches)) => {
            let output = matches.get_one::<String>("output").unwrap();
            let laps_str = matches.get_one::<String>("laps").unwrap();
            let data_per_lap_str = matches.get_one::<String>("dataPerLap").unwrap();
            let laps = laps_str.parse::<i32>().unwrap();
            let data_per_lap = data_per_lap_str.parse::<i32>().unwrap();
            create_test_file(output,laps,data_per_lap);
        }
        _ => unreachable!("wrong subcommand")
    };
     

    
}
