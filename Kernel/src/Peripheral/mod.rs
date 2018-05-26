pub mod Serial;

trait TextInterface {
    fn write(&mut self, data2write: &str);
    fn read(&self);
    fn is_available(&self);
}