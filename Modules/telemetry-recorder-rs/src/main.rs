mod acc_recorder;
mod test_file;
use acc_recorder::record_start;
use test_file::create_test_file;
use clap::Arg;
fn main() {
    let cmd = clap::Command::new("Telemetry Recorder")
    .subcommand_required(true)
    .subcommand(clap::Command::new("ACC")
        .about("Records ACC Telemetry")
        .arg(Arg::new("frequence").required(true).help("time in ms between two points"))
        .arg(Arg::new("rateFullFrame").required(true).help("how much delta frames between two full frames"))
        .arg(Arg::new("output").short('o').required(true).help("output file")))
    .subcommand(clap::Command::new("Test")
        .about("Creates a Test File")
        .arg(Arg::new("output").short('o').required(true))
        .arg(Arg::new("laps").required(true))
        .arg(Arg::new("dataPerLap").required(true)));
    let matches = cmd.get_matches();
    
    match matches.subcommand() {
        Some(("ACC",matches)) => {
            let frequence_option = matches.get_one::<String>("frequence");
            let rate_full_frame_option = matches.get_one::<String>("rateFullFrame");
            let output_arg = matches.get_one::<String>("output").unwrap();
            let output = output_arg.clone();
            let mut frequence = 10;
            if let Some(frequence_str) = frequence_option {
                frequence = frequence_str.parse::<i32>().unwrap();
            }
            let mut rate_full_frame = 10;
            if let Some(rate_full_frame_string) = rate_full_frame_option{
                rate_full_frame = rate_full_frame_string.parse::<i32>().unwrap();
            }
            let _ = record_start(output,frequence,rate_full_frame);
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
