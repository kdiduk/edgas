import sys


def read_velocities(file_path):
    timeline = []
    velocities_x = []
    velocities_y = []

    result = {
        "nparticles": 0,
        "nsnapshots": 0,
        "t": timeline,
        "vx": velocities_x,
        "vy": velocities_y,
        "valid": False
    }

    with open(file_path, 'r') as f:
        # read the first line with the time step, and ignore it
        line = f.readline()
        if not line:
            print(f"Unable to read snapshot file {file_path}")
            return result
        
        split_line = line.split()
        if len(split_line) != 1:
            print(f"Invalid format of snapshot file. First line in file: {line}")
            return result
        first_time = float(split_line[0])
        if abs(first_time) > 1.0e-10:
            print(f"First time in the snapshot file expected to be 0.0 but found {first_time}")
        
        num_particles = 0
        # calculate number of particles by counting the lines in the file,
        # but skip the first snapshot
        while True:
            line = f.readline()
            line_split = line.split()
            if len(line_split) == 1:
                tt = float(line_split[0])
                if tt <= 0:
                    print("Invalid time stamp encountered")
                    return result    
                timeline.append(tt)
                break
            num_particles += 1
        
        print(f"Number of particles: {num_particles}")
        result["nparticles"] = num_particles


        while True:
            for i in range(0, num_particles):
                line = f.readline()
                if not (line):
                    print("Invalid snapshot file format: line with particle state expected")
                    return result
                parts = line.split()
                if len(parts) < 4:
                    print("Invalid file format. Line encountered: " + line)
                    return result
                
                vx, vy = float(parts[2]), float(parts[3])
                velocities_x.append(vx)
                velocities_y.append(vy)
            
            result["nsnapshots"] += 1
            
            line = f.readline()
            if not line:
                print("End of file reached")
                break
            split_line = line.split()
            if len(split_line) != 1:
                print("Invalid file format, line with time expected but found: " + line)
                break
            
            next_time = float(split_line[0])
            if next_time < timeline[-1]:
                print(f"Invalid snapshot file format: encountered decscending time {next_time} after the timeline {timeline}")
                return result
            
            timeline.append(next_time)
        
        result["valid"] = True
        
    return result


if __name__ == "__main__":
    if (len(sys.argv) != 2):
        print("Usage: python scripts/distributions.py <velocity_file>")
        sys.exit(1)
    result = read_velocities(sys.argv[1])
    print(f"result is valid: {result['valid']}")
    print(f"number of particles: {result['nparticles']}")
    print(f"number of snapshots: {result['nsnapshots']}")
    print(f"timeline: {result['t']}")
    print(f"number of vx items: {len(result['vx'])}")
    print(f"number of vy items: {len(result['vy'])}")

# EOF
