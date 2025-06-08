# Development and Testing History

## Initial Testing Phase
- Tested register 0x0005 for power readings
- Confirmed working with scaling factor of 10
- Successfully reporting watts to Home Assistant

## Register Discovery Process
1. First Attempt:
   - Tried registers 0x0300-0x0310
   - Found register 0x302 showing 655.40
   - Value wasn't updating properly

2. Second Attempt:
   - Tested registers 0x0000-0x000F
   - Found varying values but no consistent kWh readings

3. Carlo Gavazzi Software Discovery
   - Used official Carlo Gavazzi software to verify readings
   - Found correct total energy reading: 74.6 kWh
   - Led to testing register 273
   - Discovered correct scaling factor (/10)

## Register Findings
- Register 0x0005: Power (W)
   - Updates quickly
   - Scaling factor: /10
   - Accurate readings confirmed

- Register 273: Total Energy (kWh)
   - Uses second register value
   - Scaling factor: /10
   - Matches Carlo Gavazzi software readings
   - Updates immediately with energy changes
   - Verified against separate mains monitor
   - Highly responsive and accurate

## Failed Approaches
- Register 0x302: Showed static readings
- Registers 0x400-0x600: No response
- Various scaling factors attempted (/100, /1000)
- Different Modbus function codes

## Final Implementation
- Power readings from register 0x0005
- kWh readings from register 273
- 5-second update interval (could be faster if needed)
- Home Assistant integration with utility meters for daily/weekly/monthly/yearly tracking

## Verification Testing
- Parallel testing with separate mains monitor
- kWh updates observed within 1 second of actual usage change
- No delays in ET112 reporting
- Highly accurate and responsive readings

## Lessons Learned
1. ET112 provides immediate energy reading updates
2. Carlo Gavazzi software crucial for register verification
3. Some registers show mirror data
4. Both power and energy readings update quickly and accurately
