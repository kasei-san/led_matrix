# encoding: utf-8
require File.join(File.dirname(__FILE__), '..', 'ext', 'LedController')
require File.join(File.dirname(__FILE__), 'led_dataset')
require 'thread'
require 'singleton'

class LedIntermediator
  include Singleton

  def initialize
    @mutex = Mutex.new
    @led_controller = LedController.new
    @led_dataset = LedDataSet.new('')
    @queue = Queue.new
    t = Thread.new do
      loop do
        begin
          @mutex.synchronize do
            @led_controller.matrix = @led_dataset.next
          end
        rescue => e
          e.message
        end
        sleep(0.1)
      end
    end
  end

  def set_str(str)
    @mutex.synchronize do
      @led_dataset = LedDataSet.new(str)
    end
  end
end
